#include <Socket.h>
#include <iostream>
int main()
{
    int serverSocket = tpSocket::socketCreate();
    tpSocket::socketBind(serverSocket);

    tpSocket::socketListen(serverSocket);

    int clientSocket = tpSocket::socketAccept(serverSocket);

    std::string message;
    while (message != "#close")
    {
        message = tpSocket::socketReceive(clientSocket);
        if (message != "")
            tpSocket::socketSend(clientSocket, "Message received by server: " + message);
    }

    tpSocket::socketClose(serverSocket);
    return 0;
}