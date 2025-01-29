#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>
#include <string>
#include "Socket.h"

#pragma comment(lib, "Ws2_32.lib")

namespace tpSocket
{
	inline static WSADATA wsaData;

	struct addrinfo* getAddress(std::string_view addr = "")
	{
		struct addrinfo *result, hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_UDP;

		const char* address = NULL;
		if (!addr.empty())
		{
			address = addr.data();
		}

		// Resolve the server address and port
		getaddrinfo(address, std::to_string(DEFAULT_PORT).c_str(), &hints, &result);
		return result;
	}


	int socketCreate()
	{
		int iResult;

		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed: %d\n", iResult);
			return 0;
		}

		struct addrinfo* ptr = getAddress();;
		
		int socketConnection = INVALID_SOCKET;

		// Create a SOCKET for connecting to server
		socketConnection = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);

		freeaddrinfo(ptr);

		return socketConnection;
	}

	void socketClose(int socketId)
	{
		shutdown(socketId, SD_SEND);
		closesocket(socketId);
		WSACleanup();
	}

	void socketConnect(int socketId, std::string_view serverAddress)
	{
		struct addrinfo * ptr = getAddress(serverAddress);

		// Connect to server.
		connect(socketId, ptr->ai_addr, (int)ptr->ai_addrlen);

		freeaddrinfo(ptr);
	}

	void socketSend(int socketId, std::string_view message)
	{
		send(socketId, message.data(), message.size(), 0);
	}

	std::string socketReceive(int socketId)
	{
		char receiveBuff[512];
		recv(socketId, receiveBuff, 512, 0);
		return receiveBuff;
	}

	void socketListen(int socketId)
	{
		listen(socketId, SOMAXCONN);
	}

	void socketBind(int socketId)
	{
		struct addrinfo* ptr = getAddress();

		bind(socketId, ptr->ai_addr, (int)ptr->ai_addrlen);
	}

	int socketAccept(int socketId)
	{
		return accept(socketId, NULL, NULL);
	}
}

#endif // _WIN32