#include <Socket.h>
#include <iostream>

#define SERVER_PORT 5555
#define BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
    // Validate the parameters
    if (argc != 2) {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }
    if (tpSocket::socketInit() != 0) {
        fprintf(stderr, "Failed to initialize sockets\n");
        return 1;
    }
    std::string strAddr(argv[1]);

    bool ipv4 = true;
    if (strAddr.find_first_of(':') != std::string::npos)
    {
        ipv4 = false;
    }

    // Create a socket
    SocketHandle sock = tpSocket::socketCreate(ipv4);
    if (sock < 0) {
        fprintf(stderr, "Failed to create socket\n");
        tpSocket::socketClean();
        return 1;
    }

    constexpr const char* message = "helo";

    // Send a message to the server
    if (tpSocket::socketSendTo(sock, argv[1], SERVER_PORT, message, strlen(message)) < 0) {
        fprintf(stderr, "Failed to send message to server\n");
        tpSocket::socketClose(sock);
        tpSocket::socketClean();
        return 1;
    }

    // Receive the response from the server
    char buffer[BUFFER_SIZE];
    char serverAddress[INET6_ADDRSTRLEN];
    int serverPort;

    int bytesReceived = tpSocket::socketReceive(sock, serverAddress, &serverPort, buffer, sizeof(buffer));
    if (bytesReceived > 0) {
        buffer[bytesReceived] = '\0'; // Null-terminate the string
        std::cout << buffer << '\n';
    }

    tpSocket::socketClose(sock);
    tpSocket::socketClean();
	return 0;
}