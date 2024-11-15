#ifndef SERVER_H
#define SERVER_H
#include <iostream>
#include <vector>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <wininet.h>

namespace Server
{
	class Server
	{
	public:
		void start();
		void stop();
		void restart();
	};
}

#endif // SERVER_H
