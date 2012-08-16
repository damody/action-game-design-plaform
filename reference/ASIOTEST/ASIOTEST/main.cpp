#define _WIN32_WINNT 0x0601

#include <ctime>
#include <iostream>
#include <string>
#include <vector>
#include <boost/asio.hpp>
#include <boost/enable_shared_from_this.hpp>
#include <boost/bind.hpp>
#include <boost/shared_ptr.hpp>
#include "server.h"

using boost::asio::ip::tcp;

int main()
{
	try
	{
		boost::asio::io_service io_service;
		tcp_server::pointer server = tcp_server::create(io_service);
		io_service.run();
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}

	system("pause");
	return 0;
}