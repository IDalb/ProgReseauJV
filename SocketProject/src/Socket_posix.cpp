//#ifdef unix

#include <iostream>
#include <ostream>

#include "Socket.h"
#include <string>
#include <winsock2.h>
#include <psdk_inc/_ip_types.h>

sockaddr_in getServerAddress(std::string_view address) {
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(DEFAULT_PORT);
    serverAddress.sin_addr.s_addr = inet_addr(address.data());
    return serverAddress;
}

void tpSocket::Socket::socketConnect(std::string_view serverAddress) {
    sockaddr_in serverAddressIn = getServerAddress(serverAddress);
    connect(socketConnection, reinterpret_cast<struct sockaddr *>(&serverAddressIn), sizeof(serverAddressIn));
}

void tpSocket::Socket::socketDisconnect() {
    close(socketConnection);
}

void tpSocket::Socket::socketSend(std::string_view message) {
    const char* messageData = message.data();
    send(socketConnection, messageData, message.size(), 0);
}

std::string tpSocket::Socket::socketReceive() {
    char buffer[1024] = { 0 };
    recv(clientSocket, buffer, sizeof(buffer), 0);
    std::cout << "Message du client : " << buffer << std::endl;
}


void tpSocket::Socket::socketBind(std::string_view serverAddress) {
    sockaddr_in serverAddressIn = getServerAddress(serverAddress);
    bind(socketConnection, reinterpret_cast<struct sockaddr *>(&serverAddressIn), sizeof(serverAddressIn));
}

void tpSocket::Socket::socketListen() {
    listen(socketConnection, 5);
}

void tpSocket::Socket::socketAccept() {
    int clientSocket = accept(socketConnection, nullptr, nullptr);
}

//#endif // unix
