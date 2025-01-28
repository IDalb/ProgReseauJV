#pragma once
#include <cstdio>
#include <string_view>

#define DEFAULT_PORT 5555


namespace tpSocket
{
	class Socket
	{
	public:
		Socket() = default;
		~Socket() = default;

		int socketCreate();
		void socketClose(int socketId);
		
		void socketConnect(int socketId, std::string_view serverAddress);
		
		void socketSend(int socketId, std::string_view message);
		std::string socketReceive(int socketId);
		
		void socketListen(int socketId);
		void socketBind(int socketId);
		int socketAccept(int socketId);
	private:
	};
}