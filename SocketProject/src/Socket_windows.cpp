#ifdef _WIN32

#include "Socket.h"
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "ws2_32.lib")

namespace tpSocket
{
	int socketInit()
	{
		WSADATA wsaData;
		return WSAStartup(MAKEWORD(2, 2), &wsaData);
	}

	void socketClean()
	{
		WSACleanup();
	}

	void socketClose(SocketHandle sock)
	{
		closesocket(sock);
	}
}

#endif // _WIN32