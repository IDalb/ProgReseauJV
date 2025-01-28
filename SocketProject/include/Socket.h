#pragma once
#include <string_view>

#define DEFAULT_PORT "5555"


namespace tpSocket
{
	class Socket
	{
	public:
		Socket(std::string_view serverAddress);
		~Socket();
		
		void connect();
		void disconnect();
		
		void send();
		void listen();
	};
}