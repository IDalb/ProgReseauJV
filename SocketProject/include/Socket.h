#pragma once
#include <cstdio>
#include <string_view>

#define DEFAULT_PORT "5555"


namespace tpSocket
{
	class Socket
	{
	public:
		Socket();
		~Socket();
		
		void socketConnect(std::string_view serverAddress);
		void socketDisconnect();
		
		void socketSend(std::string_view message);
		std::string socketListen();
	private:
		int socketConnection{};
	};
}