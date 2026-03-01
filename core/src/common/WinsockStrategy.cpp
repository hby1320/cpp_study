#include <common/WinsockStrategy.h>
#include <iostream>

#ifdef _WIN32
#include <winsock2.h>
#include <ws2tcpip.h>
#pragma comment(lib, "Ws2_32.lib")
#endif

WinsockStrategy::WinsockStrategy() {
#ifdef _WIN32
    WSAStartup(MAKEWORD(2,2), &wsaData_);
    sock_ = INVALID_SOCKET;
    client_ = INVALID_SOCKET;
#endif
}

WinsockStrategy::~WinsockStrategy() {
    close();
#ifdef _WIN32
    WSACleanup();
#endif
}

bool WinsockStrategy::create() {
#ifdef _WIN32
    sock_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    return sock_ != INVALID_SOCKET;
#else
    return false;
#endif
}

bool WinsockStrategy::bind(int port) {
#ifdef _WIN32
    struct sockaddr_in service;
    service.sin_family = AF_INET;
    service.sin_addr.s_addr = INADDR_ANY;
    service.sin_port = htons(port);
    return ::bind(sock_, (SOCKADDR*)&service, sizeof(service)) == 0;
#else
    return false;
#endif
}

bool WinsockStrategy::listen() {
#ifdef _WIN32
    return ::listen(sock_, SOMAXCONN) == 0;
#else
    return false;
#endif
}

bool WinsockStrategy::accept() {
#ifdef _WIN32
    client_ = ::accept(sock_, NULL, NULL);
    return client_ != INVALID_SOCKET;
#else
    return false;
#endif
}

bool WinsockStrategy::connect(const char* address, int port) {
#ifdef _WIN32
    struct sockaddr_in clientService;
    clientService.sin_family = AF_INET;
    clientService.sin_addr.s_addr = inet_addr(address);
    clientService.sin_port = htons(port);
    return ::connect(sock_, (SOCKADDR*)&clientService, sizeof(clientService)) == 0;
#else
    return false;
#endif
}

bool WinsockStrategy::send(const char* data, int len) {
#ifdef _WIN32
    SOCKET fd = client_ != INVALID_SOCKET ? client_ : sock_;
    return ::send(fd, data, len, 0) == len;
#else
    return false;
#endif
}

int WinsockStrategy::receive(char* buffer, int len) {
#ifdef _WIN32
    SOCKET fd = client_ != INVALID_SOCKET ? client_ : sock_;
    return ::recv(fd, buffer, len, 0);
#else
    return -1;
#endif
}

void WinsockStrategy::close() {
#ifdef _WIN32
    if (client_ != INVALID_SOCKET) closesocket(client_);
    if (sock_ != INVALID_SOCKET) closesocket(sock_);
    client_ = INVALID_SOCKET;
    sock_ = INVALID_SOCKET;
#endif
}

