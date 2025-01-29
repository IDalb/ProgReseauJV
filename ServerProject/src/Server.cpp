#include <Socket.h>
#include <iostream>

#include <string>

#define PORT 5555
#define BUFFER_SIZE 1024

int main(int argc, char* argv[])
{
    // Validate the parameters
    bool ipv4 = false;
    if (argc == 2) {
        std::string stdArg(argv[1]);
        if (stdArg == "ipv4")
        {
            ipv4 = true;
        }
    }
    
    if (tpSocket::socketInit() != 0) {
        fprintf(stderr, "Failed to initialize sockets\n");
        return 1;
    }

    SocketHandle sock = tpSocket::socketCreate(ipv4);
    if (sock < 0) {
        fprintf(stderr, "Failed to create socket\n");
        tpSocket::socketClean();
        return 1;
    }

    // Bind the socket to port
    if (tpSocket::socketBind(sock, PORT, ipv4) != 0) {
        fprintf(stderr, "Failed to bind socket to port %d\n", PORT);
        tpSocket::socketClose(sock);
        tpSocket::socketClean();
        return 1;
    }

    printf("Server listening on port %d...\n", PORT);

    char buffer[BUFFER_SIZE];
    char clientAddress[INET6_ADDRSTRLEN];
    int clientPort;

    while (1) {
        int bytesReceived = tpSocket::socketReceive(sock, clientAddress, &clientPort, buffer, sizeof(buffer));
        if (bytesReceived > 0) {
            buffer[bytesReceived] = '\0'; // Null-terminate the string
            printf("Received from %s:%d - %s\n", clientAddress, clientPort, buffer);

            // Echo back the message to the client
            tpSocket::socketSendTo(sock, clientAddress, clientPort, buffer, bytesReceived);
        }
    }

    tpSocket::socketClose(sock);
    tpSocket::socketClean();
    return 0;
}