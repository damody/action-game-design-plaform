#pragma once

#include <ctime>
#include <iterator>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include "message.h"
#include "defines.h"
#include "boost/thread/mutex.hpp"
extern boost::mutex mtx;

using boost::asio::ip::tcp;

std::string make_daytime_string()
{
	using namespace std; // For time_t, time and ctime;
	time_t now = time(0);
	return ctime(&now);
}

class tcp_connection
	: public boost::enable_shared_from_this<tcp_connection>
{
public:
	typedef boost::shared_ptr<tcp_connection> pointer;

	static pointer create(boost::asio::io_service& io_service/*, tcp_server::pointer server*/)
	{
		return pointer(new tcp_connection(io_service/*, server*/));
	}

	tcp::socket& socket()
	{
		return socket_;
	}

	boost::array<char, COMMAND_TOTAL_SIZE>& getCommand()
	{
		return command_;
	}

	boost::asio::streambuf& getCommandMessage()
	{
		return commmandMessage;
	}

	bool available()
	{
		return !disconnected;
	}

	void sendMessage(message& mes)
	{
		

		char command[COMMAND_TOTAL_SIZE+1];
		message2_ = "SENDMESSAGE";

		messages_.push_back(mes);
		boost::asio::streambuf stream;
		boost::archive::binary_oarchive archive(stream);
		archive << mes;
		/*{
			std::ofstream ofs("asd", std::ios_base::trunc);
			boost::archive::binary_oarchive ar(ofs);
			ar << mes;
		}
		{
			std::ifstream ifs("asd");
			boost::archive::binary_iarchive ar(ifs);
			ar >> mess;
		}*/

		messagesStr.push_back(boost::asio::buffer(stream.data()));
		//std::cout << messagesStr.back().length() << std::endl;

		sprintf(command, "%-*s %.*d", COMMAND_TYPE_SIZE, message2_.c_str(), COMMAND_LENGTH_SIZE, buffer_size(stream.data()));
		message2_ = std::string(command);

		commandStr.push_back(boost::asio::buffer(message2_));

		boost::asio::async_write(socket_, commandStr.back(),
			boost::bind(&tcp_connection::handle_command_write, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
		//boost::asio::write(socket_, boost::asio::buffer(message2_));

		boost::asio::async_write(socket_, messagesStr.back(),
			boost::bind(&tcp_connection::handle_command_message_write, shared_from_this(),
			boost::asio::placeholders::error,
			boost::asio::placeholders::bytes_transferred));
	}

private:
	tcp_connection(boost::asio::io_service& io_service)
		: socket_(io_service), disconnected(FALSE), sendedMessage(0)
	{
	}

	void handle_command_write(const boost::system::error_code& error,
		size_t bytes_transferred)
	{
		//std::cout << bytes_transferred << std::endl;
		if(error)
		{
			disconnected = TRUE;
		}
	}

	void handle_command_message_write(const boost::system::error_code& error,
		size_t bytes_transferred)
	{
		//std::cout << bytes_transferred << std::endl;
		if(error)
		{
			disconnected = TRUE;
		}

		sendedMessage++;

		if(sendedMessage == messagesStr.size() && messagesStr.size() >= 30)
		{
			commandStr.clear();
			messages_.clear();
			messagesStr.clear();
			sendedMessage = 0;
		}
	}

	bool disconnected;
	tcp::socket socket_;
	boost::array<char, COMMAND_TOTAL_SIZE> command_;
	boost::asio::streambuf commmandMessage;
	std::vector<message> messages_;
	std::vector<boost::asio::const_buffers_1> commandStr;
	std::vector<boost::asio::const_buffers_1> messagesStr;
	std::string message_;
	std::string message2_;
	unsigned int sendedMessage;
	/*tcp_server::pointer server;*/
};