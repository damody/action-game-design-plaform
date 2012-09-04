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
#include <fstream>

using boost::asio::ip::tcp;
std::ofstream logFile;

int main()
{
	//try
	{
		std::time_t now = time(0);
		std::string time(std::ctime(&now));

		char str[256];
		sprintf(str, "ServerLog_%s.txt", time.c_str());

		for(int i=0;i<strlen(str);i++)
		{
			if(str[i]==':' || str[i]==' ' || str[i]==10)
				str[i] = '_';
		}

		logFile.open(str);

		boost::asio::io_service io_service;
		tcp_server::pointer server = tcp_server::create(io_service);
		io_service.run();
	}
	/*catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}*/

	system("pause");
	return 0;
}