#include "Socket.h"
#include <iostream>

namespace tpSocket
{
	SocketHandle socketCreate(bool useIpv4)
	{
		if (useIpv4)
		{
			// Create two sockets, one for IPv4 and another for IPv6
			SocketHandle sock_v4 = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
			if (sock_v4 == INVALID) {
				printf("IPv4 socket creation failed");
				return INVALID;
			}
			return sock_v4; // Return the IPv6 socket for binding, or you can handle both separately.
		}
		else
		{
			SocketHandle sock_v6 = socket(AF_INET6, SOCK_DGRAM, IPPROTO_UDP);
			if (sock_v6 == INVALID) {
				printf("IPv6 socket creation failed");
				socketClose(sock_v6);
				return INVALID;
			}
			return sock_v6; // Return the IPv6 socket for binding, or you can handle both separately.
		}

	}

	int socketBind(SocketHandle sock, int port, bool useIpv4)
	{
		if (useIpv4)
		{
			// Now bind the IPv4 socket, if applicable
			struct sockaddr_in addr4 = { 0 };
			addr4.sin_family = AF_INET;
			addr4.sin_port = htons(port);
			addr4.sin_addr.s_addr = htonl(INADDR_ANY);

			if (bind(sock, (struct sockaddr*)&addr4, sizeof(addr4)) != 0) {
				printf("IPv4 bind failed");
				return -1;
			}
		}
		else
		{
			// Bind the IPv6 socket first
			struct sockaddr_in6 addr6 = { 0 };
			addr6.sin6_family = AF_INET6;
			addr6.sin6_port = htons(port);
			addr6.sin6_addr = in6addr_any;
			int option = 0;  // 0 means allow both IPv4 and IPv6 connections
			setsockopt(sock, IPPROTO_IPV6, IPV6_V6ONLY, (connectionOption)&option, sizeof(option));
			if (bind(sock, (struct sockaddr*)&addr6, sizeof(addr6)) != 0) {
				printf("IPv6 bind failed");
				return -1;
			}
		}
		return 0;
	}

	int socketReceive(SocketHandle sock, char* address, int* port, char* buffer, size_t size) {
		struct sockaddr_storage addrStorage;
		sockSize addrLen = sizeof(addrStorage);
		int receivedBytes = recvfrom(sock, buffer, size, 0, (struct sockaddr*)&addrStorage, &addrLen);
		if (receivedBytes < 0) {
			printf("recvfrom failed");
			return -1;
		}

		if (addrStorage.ss_family == AF_INET) {  // IPv4
			struct sockaddr_in* addr4 = (struct sockaddr_in*)&addrStorage;
			inet_ntop(AF_INET, &addr4->sin_addr, address, INET_ADDRSTRLEN);
			*port = ntohs(addr4->sin_port);
		}
		else if (addrStorage.ss_family == AF_INET6) {  // IPv6
			struct sockaddr_in6* addr6 = (struct sockaddr_in6*)&addrStorage;
			inet_ntop(AF_INET6, &addr6->sin6_addr, address, INET6_ADDRSTRLEN);
			*port = ntohs(addr6->sin6_port);
		}

		return receivedBytes;
	}

	int socketSendTo(SocketHandle sock, const char* address, int port, const char* data, size_t size) {
		struct sockaddr_storage addrStorage = { 0 };
		struct sockaddr_in* addr4 = (struct sockaddr_in*)&addrStorage;
		struct sockaddr_in6* addr6 = (struct sockaddr_in6*)&addrStorage;

		// Check if it's an IPv6 address or IPv4 address
		if (strchr(address, ':')) {  // IPv6 address
			addr6->sin6_family = AF_INET6;
			addr6->sin6_port = htons(port);
			if (inet_pton(AF_INET6, address, &addr6->sin6_addr) <= 0) {
				printf("inet_pton (IPv6) failed");
				return -1;
			}
		}
		else {  // IPv4 address
			addr4->sin_family = AF_INET;
			addr4->sin_port = htons(port);
			if (inet_pton(AF_INET, address, &addr4->sin_addr) <= 0) {
				printf("inet_pton (IPv4) failed");
				return -1;
			}
		}

		int sentBytes = sendto(sock, data, size, 0, (struct sockaddr*)&addrStorage, sizeof(addrStorage));
		if (sentBytes < 0) {
			printf("sendto failed");
		}
		return sentBytes;
	}

}