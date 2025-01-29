#pragma once
#include <stddef.h>
#include <cstring>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
# define INVALID INVALID_SOCKET
typedef SOCKET SocketHandle;
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
# include <sys/types.h>
# include <sys/time.h>
# include <netdb.h>
typedef int SocketHandle;
# define INVALID -1
#endif


namespace tpSocket
{
	int socketInit();
	void socketClean();

	SocketHandle socketCreate(bool useIpv4 = true);
	void socketClose(SocketHandle sock);
				
	int socketSendTo(SocketHandle sock, const char* address, int port, const char* data, size_t size);
	int socketReceive(SocketHandle sock, char* outAddress, int* outPort, char* buffer, size_t bufferSize);
	
	int socketBind(SocketHandle sock, int port, bool useIpv4 = true);
}