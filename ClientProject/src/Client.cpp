#include <Socket.h>
#include <iostream>
int main(int argc, char* argv[])
{
    // Validate the parameters
    if (argc != 2) {
        printf("usage: %s server-name\n", argv[0]);
        return 1;
    }
	int socketId = tpSocket::socketCreate();
    tpSocket::socketConnect(socketId, argv[1]);

    tpSocket::socketSend(socketId, "helo");
    std::string message;
    do
    {
        message = tpSocket::socketReceive(socketId);
    } while (message != "");

    std::cout << message;
    std::cin;

    tpSocket::socketClose(socketId);
	return 0;
}