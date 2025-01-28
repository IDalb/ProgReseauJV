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
		
		void socketSend();
		void socketListen();
	private:
		int socketConnection{};
	};
}