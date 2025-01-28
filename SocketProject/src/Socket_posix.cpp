#ifdef unix

#include "Socket.h"

#include <string>
#include <iostream>
#include <netinet/in.h>
#include <sys/socket.h>

sockaddr_in getServerAddress() {
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(DEFAULT_PORT);
    return serverAddress;
}

void tpSocket::Socket::socketConnect(const int socketId, std::string_view serverAddress) {
    sockaddr_in serverAddress = getServerAddress();
    serverAddress.sin_addr.s_addr = inet_addr(address.data());
    connect(socketId, reinterpret_cast<struct sockaddr *>(&serverAddress), sizeof(serverAddress));
}

int tpSocket::Socket::socketCreate() {
    return socket(AF_INET, SOCK_STREAM, 0);
}


void tpSocket::Socket::socketClose(const int socketId) {
    close(socketId);
}

void tpSocket::Socket::socketSend(const int socketId, std::string_view message) {
    const char* messageData = message.data();
    send(socketId, messageData, message.size(), 0);
}

std::string tpSocket::Socket::socketReceive(const int socketId) {
    char buffer[1024] = { 0 };
    recv(socketId, buffer, sizeof(buffer), 0);
    std::cout << "Message du client : " << buffer << std::endl;
}


void tpSocket::Socket::socketBind(const int socketId) {
    sockaddr_in serverAddress = getServerAddress();
    serverAddress.sin_addr.s_addr = INADDR_ANY;
    bind(socketId, reinterpret_cast<struct sockaddr *>(&serverAddress), sizeof(serverAddress));
}

void tpSocket::Socket::socketListen(const int socketId) {
    listen(socketId, 5);
}

int tpSocket::Socket::socketAccept(const int socketId) {
    return accept(socketId, nullptr, nullptr);
}

#endif // unix
