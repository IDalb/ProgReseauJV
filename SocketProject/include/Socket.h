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
		
		void connect(std::string_view serverAddress);
		void disconnect();
		
		void send();
		void listen();
	private:
		int socketConnection{};
	};
}