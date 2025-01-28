#pragma once
#include <cstdio>
#include <string_view>

#define DEFAULT_PORT 5555


namespace tpSocket
{
	class Socket
	{
	public:
		Socket();
		~Socket();
		
		void socketConnect(int sockedId, std::string_view serverAddress);
		void socketDisconnect(int sockedId);
		
		void socketSend(int sockedId, std::string_view message);
		std::string socketReceive(int sockedId);
		
		void socketListen(int sockedId);
		void socketBind(int sockedId);
		void socketAccept(int sockedId);
	private:
	};
}