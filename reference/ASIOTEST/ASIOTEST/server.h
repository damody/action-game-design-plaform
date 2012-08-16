#pragma once

#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include "connection.h"
#include "message.h"

using boost::asio::ip::tcp;

class tcp_server
	: public boost::enable_shared_from_this<tcp_server>
{
public:
	typedef boost::shared_ptr<tcp_server> pointer;
	static pointer create(boost::asio::io_service& io_service)
	{
		return pointer(new tcp_server(io_service));
	}

	void disconnectPlayer(tcp_connection::pointer player)
	{

	}

private:
	tcp_server(boost::asio::io_service& io_service)
		: acceptor_(io_service, tcp::endpoint(tcp::v4(), 7777)), messageTimer(io_service, boost::posix_time::seconds(1))
	{
		start_accept();

		/*std::time_t now = time(0);
		strcpy(mes2.sender, "System");
		strcpy(mes2.text, "Welcome.");
		char dat[64];
		strcpy(dat, std::ctime(&now));
		dat[strlen(dat)-1] = 0;
		strcpy(mes2.time, dat);

		messageTimer.async_wait(boost::bind(&tcp_server::broadcastMessage, this, mes2));*/
	}
	void broadcastMessage(message& mes)
	{
		/*char command[COMMAND_TOTAL_SIZE+1];

		boost::asio::streambuf stream;
		boost::archive::binary_oarchive archive(stream);
		archive << mes;
		sprintf(command, "%-*s %.*d", COMMAND_TYPE_SIZE, "SENDMESSAGE", COMMAND_LENGTH_SIZE, buffer_size(stream.data()));

		messagePool.push_back(boost::asio::buffer(std::string(command)));
		messagePool.push_back(boost::asio::buffer(stream.data()));*/

		for(size_t i=0;i<players.size();i++)
		{
			if(players[i]->available())
			{
				std::cout << "Sending message to client " + players[i]->socket().remote_endpoint().address().to_string() + ":"
					<< players[i]->socket().remote_endpoint().port()
					<< std::endl;
				players[i]->sendMessage(mes);
			}
			else
			{
				std::cout << "Disconnected client " + players[i]->socket().remote_endpoint().address().to_string() + ":"
					<< players[i]->socket().remote_endpoint().port()
					<< std::endl;
				disconnectPlayer(players[i]);
			}
		}

		/*std::time_t now = time(0);
		char dat[64];
		strcpy(dat, std::ctime(&now));
		dat[strlen(dat)-1] = 0;
		strcpy(mes.time, dat);

		messageTimer.expires_at(messageTimer.expires_at() + boost::posix_time::milliseconds(1000));
		messageTimer.async_wait(boost::bind(&tcp_server::broadcastMessage, this, mes));*/
	}
	void start_accept()
	{
		tcp_connection::pointer new_connection =
			tcp_connection::create(acceptor_.get_io_service());

		acceptor_.async_accept(new_connection->socket(),
			boost::bind(&tcp_server::handle_accept, this, new_connection,
			boost::asio::placeholders::error));
	}
	void handle_accept(tcp_connection::pointer new_connection,
		const boost::system::error_code& error)
	{
		if (!error)
		{
			std::cout << "Accepted client " + new_connection->socket().remote_endpoint().address().to_string() + ":"
				<< new_connection->socket().remote_endpoint().port()
				<< std::endl;
			players.push_back(new_connection);

			boost::asio::async_read(new_connection->socket(),
				boost::asio::buffer(new_connection->getCommand()),
				boost::bind(&tcp_server::handle_command_read, shared_from_this(), boost::asio::placeholders::error, new_connection)
				);
		}

		start_accept();
	}
	void handle_command_read(const boost::system::error_code& error, tcp_connection::pointer player)
	{
		if (error == boost::asio::error::eof)
		{
			disconnectPlayer(player);
			return;
		}
		else if (error)
		{
			//throw boost::system::system_error(error); // Some other error.
			disconnectPlayer(player);
			return;
		}

		char commandType[COMMAND_TYPE_SIZE+1];
		int commandBytes = 0;
		sscanf(player->getCommand().data(), "%s %d", commandType, &commandBytes);

		boost::asio::async_read(player->socket(),
			player->getCommandMessage(),
			boost::asio::transfer_at_least(commandBytes),
			boost::bind(&tcp_server::handle_command_message_read, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred, player)
			);
	}

	void handle_command_message_read(const boost::system::error_code& error, std::size_t bytes_transferred, tcp_connection::pointer player)
	{
		if (error == boost::asio::error::eof)
		{
			disconnectPlayer(player);
			return;
		}
		else if (error)
		{
			//throw boost::system::system_error(error); // Some other error.
			disconnectPlayer(player);
			return;
		}

		char commandType[COMMAND_TYPE_SIZE+1];
		int commandBytes = 0;
		sscanf(player->getCommand().data(), "%s %d", commandType, &commandBytes);

		if(std::string("SENDMESSAGE").compare(commandType) == 0)
		{
			std::istream is(&player->getCommandMessage());
			boost::archive::binary_iarchive ar(is);
			message mes;
			ar & mes;

			broadcastMessage(mes);
		}

		player->getCommand().assign(0);
		player->getCommandMessage().consume(player->getCommandMessage().size());
		boost::asio::async_read(player->socket(),
			boost::asio::buffer(player->getCommand()),
			boost::bind(&tcp_server::handle_command_read, shared_from_this(), boost::asio::placeholders::error, player)
			);
	}

	tcp::acceptor acceptor_;
	boost::asio::deadline_timer messageTimer;
	std::vector<tcp_connection::pointer> players;
	std::vector<boost::asio::const_buffers_1> messagePool;
	message mes2;
};