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

	void getAddress(struct addrinfo* result, struct addrinfo hints, std::string_view addr)
	{
		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_UDP;

		// Resolve the server address and port
		getaddrinfo(addr.data(), std::to_string(DEFAULT_PORT).c_str(), &hints, &result);
	}


	int Socket::create()
	{
		int iResult;

		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed: %d\n", iResult);
			return 0;
		}

		struct addrinfo* result = NULL,
			* ptr = NULL,
			hints;
		getAddress(result, hints, NULL);
		
		int socketConnection = INVALID_SOCKET;
		ptr = result;

		// Create a SOCKET for connecting to server
		socketConnection = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);

		freeaddrinfo(result);

		return socketConnection;
	}

	void Socket::destroy(int socketId)
	{
		closesocket(socketId);
		WSACleanup();
	}

	void Socket::socketConnect(int socketId, std::string_view serverAddress)
	{
		struct addrinfo* result = NULL,
			* ptr = NULL,
			hints;

		getAddress(result, hints, serverAddress);

		// Connect to server.
		connect(socketId, ptr->ai_addr, (int)ptr->ai_addrlen);

		freeaddrinfo(result);
	}

	void Socket::socketDisconnect(int socketId)
	{
		shutdown(socketId, SD_SEND);
	}

	void Socket::socketSend(int socketId, std::string_view message)
	{
		send(socketId, message.data(), message.size(), 0);
	}

	std::string Socket::socketReceive(int socketId)
	{
		char receiveBuff[512];
		recv(socketId, receiveBuff, 512, 0);
		return receiveBuff;
	}

	void Socket::socketListen(int socketId)
	{
		listen(socketId, SOMAXCONN);
	}

	void Socket::socketBind(int socketId)
	{
		struct addrinfo* result = NULL,
			* ptr = NULL,
			hints;

		getAddress(result, hints, NULL);
		bind(socketId, result->ai_addr, (int)result->ai_addrlen);
	}

	int Socket::socketAccept(int socketId)
	{
		return accept(socketId, NULL, NULL);
	}
}

#endif // _WIN32