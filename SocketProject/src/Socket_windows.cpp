#ifdef _WIN32
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <stdio.h>

#include "Socket.h"

#pragma comment(lib, "Ws2_32.lib")

namespace tpSocket
{
	inline static WSADATA wsaData;

	Socket::Socket()
	{
		int iResult;

		// Initialize Winsock
		iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
		if (iResult != 0) {
			printf("WSAStartup failed: %d\n", iResult);
			return;
		}

		struct addrinfo* result = NULL,
			* ptr = NULL,
			hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_UDP;

		int iResult;
		// Resolve the server address and port
		iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed: %d\n", iResult);
			WSACleanup();
			return;
		}
		socketConnection = INVALID_SOCKET;
		
		// Attempt to connect to the first address returned by
		// the call to getaddrinfo
		ptr = result;

		// Create a SOCKET for connecting to server
		socketConnection = socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);

		if (socketConnection == INVALID_SOCKET) {
			printf("Error at socket(): %ld\n", WSAGetLastError());
			freeaddrinfo(result);
			WSACleanup();
			return;
		}
	}

	Socket::~Socket()
	{
		closesocket(socketConnection);
		WSACleanup();
	}

	void Socket::socketConnect(std::string_view serverAddress)
	{
		struct addrinfo* result = NULL,
			* ptr = NULL,
			hints;

		ZeroMemory(&hints, sizeof(hints));
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;
		hints.ai_protocol = IPPROTO_UDP;

		int iResult;
		// Resolve the server address and port
		iResult = getaddrinfo(serverAddress.data(), DEFAULT_PORT, &hints, &result);
		if (iResult != 0) {
			printf("getaddrinfo failed: %d\n", iResult);
			WSACleanup();
			return;
		}
		// Connect to server.
		iResult = connect(socketConnection, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			closesocket(socketConnection);
			socketConnection = INVALID_SOCKET;
		}

		// Should really try the next address returned by getaddrinfo
		// if the connect call failed
		// But for this simple example we just free the resources
		// returned by getaddrinfo and print an error message

		freeaddrinfo(result);

		if (socketConnection == INVALID_SOCKET) {
			printf("Unable to connect to server!\n");
			WSACleanup();
			return;
		}
	}

	void Socket::socketDisconnect()
	{
		int iResult;
		// shutdown the send half of the connection since no more data will be sent
		iResult = shutdown(socketConnection, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed: %d\n", WSAGetLastError());
			closesocket(socketConnection);
			WSACleanup();
			return;
		}
	}

	void Socket::socketSend(std::string_view message)
	{
		int iResult;

		// Send an initial buffer
		iResult = send(socketConnection, message.data(), message.size(), 0);
		if (iResult == SOCKET_ERROR) {
			printf("send failed: %d\n", WSAGetLastError());
			closesocket(socketConnection);
			WSACleanup();
			return;
		}
	}

	std::string Socket::socketReceive()
	{
		char receiveBuff[512];
		recv(socketConnection, receiveBuff, 512, 0);
		return receiveBuff;
	}

	void Socket::socketListen()
	{
		
	}

	void Socket::socketBind()
	{
		int iResult;
		iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
		if (iResult == SOCKET_ERROR) {
			printf("bind failed with error: %d\n", WSAGetLastError());
			freeaddrinfo(result);
			closesocket(ListenSocket);
			WSACleanup();
			return 1;
	}
	void Socket::socketAccept()
	{
	}
}

#endif // _WIN32