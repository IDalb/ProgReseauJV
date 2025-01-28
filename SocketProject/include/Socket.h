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

		int create();
		void destroy(int socketId);
		
		void socketConnect(int socketId, std::string_view serverAddress);
		void socketDisconnect(int socketId);
		
		void socketSend(int socketId, std::string_view message);
		std::string socketReceive(int socketId);
		
		void socketListen(int socketId);
		void socketBind(int socketId);
		void socketAccept(int socketId);
	private:
	};
}