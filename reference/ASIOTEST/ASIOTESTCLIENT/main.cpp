#define _WIN32_WINNT 0x0601

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <message.h>
#include <Windows.h>
#include <defines.h>

using boost::asio::ip::tcp;

boost::asio::io_service io_service;
tcp::socket socket_(io_service);
boost::array<char, COMMAND_TOTAL_SIZE> buf;
boost::asio::streambuf buf2;
std::vector<message> inputMessage;
std::vector<bool> messageProcessed;
int lastProcessedMessage = -1;
std::string playerName;

void handle_command_read(const boost::system::error_code& error);
void handle_command_message_read(const boost::system::error_code& error, std::size_t bytes_transferred, std::string& commandType, int commandBytes);

DWORD WINAPI thread_function(LPVOID param)
{
/*
	for (int n = 0; n < 3; n++)
	{
		std::cout << "Look at me!, I'm a thread with id = " << GetCurrentThreadId() << std::endl;
		Sleep(750);
	}

	DWORD ret;
	std::cout << "Now give me a value to return: ";
	std::cin >> ret;
*/

	char text[256];

	int i=0;

	for(;;)
	{
#ifdef _DEBUG
		if(i % 1000000 != 0)
		{
			i++;
			continue;
		}
#else
		if(i % 10000000 != 0)
		{
			i++;
			continue;
		}
#endif
		text[0] = 0;
		//scanf("%[^\n]s", text);
		strcpy(text, "Hello Stress TEST.");
		if(strlen(text))
		{
			message mes;
			std::time_t now = time(0);
			strcpy(mes.sender, playerName.c_str());
			strcpy(mes.text, text);
			char dat[64];
			strcpy(dat, std::ctime(&now));
			dat[strlen(dat)-1] = 0;
			strcpy(mes.time, dat);

			boost::asio::streambuf stream;
			boost::archive::binary_oarchive archive(stream);
			archive << mes;

			char command[COMMAND_TOTAL_SIZE+1];

			sprintf(command, "%-*s %.*d", COMMAND_TYPE_SIZE, "SENDMESSAGE", COMMAND_LENGTH_SIZE, buffer_size(stream.data()));

			inputMessage.push_back(mes);
			boost::asio::write(socket_, boost::asio::buffer(std::string(command)));
			boost::asio::write(socket_, boost::asio::buffer(stream.data()));

			//printf("Send message: %s completed\n", command);
		}

		std::fflush(stdin);

		i = 1;
	}

	return 1;
}

int main(int argc, char* argv[])
{
	try
	{
		/*if (argc != 2)
		{
			std::cerr << "Usage: client <host>" << std::endl;
			return 1;
		}*/

		char pName[64+1];
		char ip[16];
		char port[6];

		printf("Please enter your name: ");
		scanf("%[^\n]s", pName);
		playerName = pName;
		std::fflush(stdin);
		printf("Please enter the host's ip: ");
		scanf("%s", ip);
		std::fflush(stdin);
		printf("Please enter the host's port: ");
		scanf("%s", port);
		std::fflush(stdin);

		tcp::resolver resolver(io_service);
		tcp::resolver::query query(ip, port);
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);
		boost::asio::connect(socket_, endpoint_iterator);

		boost::asio::async_read(socket_,
			boost::asio::buffer(buf),
			boost::bind(handle_command_read, boost::asio::placeholders::error)
			);

		DWORD thread_id;
		HANDLE hthread = CreateThread(NULL, 0, thread_function, NULL, 0, &thread_id);
		if (hthread == NULL)
		{
			std::cout << "CreateThread() failed, last error = " << GetLastError() << std::endl;
			return 1;
		}

		/*for (;;)
		{
			//boost::array<char, COMMAND_TOTAL_SIZE> buf;
			//boost::asio::streambuf buf2;
			boost::system::error_code error;

			size_t len = boost::asio::read(socket, boost::asio::buffer(buf), error);
			if (error == boost::asio::error::eof)
				break; // Connection closed cleanly by peer.
			else if (error)
				throw boost::system::system_error(error); // Some other error.

			std::cout.write(buf.data(), len);
			std::cout << std::endl;
			char commandType[COMMAND_TYPE_SIZE+1];
			int commandBytes = 0;
			sscanf(buf.data(), "%s %d", commandType, &commandBytes);
			buf.assign(0);

			if(std::string("SENDMESSAGE").compare(commandType) == 0)
			{
				len = boost::asio::read(socket, buf2, boost::asio::transfer_exactly(commandBytes), error);
				if (error == boost::asio::error::eof)
					break; // Connection closed cleanly by peer.
				else if (error)
					throw boost::system::system_error(error); // Some other error.

				std::istream is(&buf2);
				//char stt[1419];
				//is.get(stt, 1419);
				//std::cout.write(stt, len);
				//std::cout << std::endl << len << std::endl;
				boost::archive::binary_iarchive ar(is);
				message mes;
				ar & mes;

				std::cout << "[" << mes.time << "]" << mes.sender << ":" << mes.text << std::endl;

				buf2.consume(len);
			}
		}*/

		io_service.run();

		socket_.shutdown(boost::asio::ip::tcp::socket::shutdown_both);
		socket_.close();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
	
	system("pause");
	return 0;
}

void handle_command_read(const boost::system::error_code& error)
{
	if (error == boost::asio::error::eof)
	{
		return;
	}
	else if (error)
		throw boost::system::system_error(error); // Some other error.

	char commandType[COMMAND_TYPE_SIZE+1];
	int commandBytes = 0;
	sscanf(buf.data(), "%s %d", commandType, &commandBytes);

	std::string command(commandType);

	buf.assign(0);
	boost::asio::async_read(socket_,
		buf2,
		boost::asio::transfer_at_least(commandBytes),
		boost::bind(handle_command_message_read, boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, command, commandBytes)
		);
}

void handle_command_message_read(const boost::system::error_code& error, std::size_t bytes_transferred, std::string& commandType, int commandBytes)
{
	if (error == boost::asio::error::eof)
	{
		return;
	}
	else if (error)
		throw boost::system::system_error(error); // Some other error.
	else if (commandBytes != bytes_transferred)
		return;


	if(std::string("SENDMESSAGE").compare(commandType) == 0)
	{
		std::istream is(&buf2);
		//char stt[1419];
		//is.get(stt, 1419);
		//std::cout.write(stt, len);
		//std::cout << std::endl << len << std::endl;
		boost::archive::binary_iarchive ar(is);
		message mes;
		ar & mes;

		//if(playerName.compare(mes.sender) != 0)
			std::cout << "[" << mes.time << "]" << mes.sender << ":" << mes.text << std::endl;
	}


	buf2.consume(bytes_transferred);
	boost::asio::async_read(socket_,
		boost::asio::buffer(buf),
		boost::bind(handle_command_read, boost::asio::placeholders::error)
		);
}