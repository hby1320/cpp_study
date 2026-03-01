#include "TCPSocketStrategy.h"
#include <iostream>

TCPSocketStrategy::TCPSocketStrategy() : sockfd_(-1), clientfd_(-1) {
    memset(&addr_, 0, sizeof(addr_));
}

TCPSocketStrategy::~TCPSocketStrategy() {
    close();
}

bool TCPSocketStrategy::create() {
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    return sockfd_ != -1;
}

bool TCPSocketStrategy::bind(int port) {
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = INADDR_ANY;
    addr_.sin_port = htons(port);
    return ::bind(sockfd_, (struct sockaddr*)&addr_, sizeof(addr_)) == 0;
}

bool TCPSocketStrategy::listen() {
    return ::listen(sockfd_, 3) == 0;
}

bool TCPSocketStrategy::accept() {
    socklen_t addrlen = sizeof(addr_);
    clientfd_ = ::accept(sockfd_, (struct sockaddr*)&addr_, &addrlen);
    return clientfd_ != -1;
}

bool TCPSocketStrategy::connect(const char* address, int port) {
    addr_.sin_family = AF_INET;
    addr_.sin_port = htons(port);
    if (inet_pton(AF_INET, address, &addr_.sin_addr) <= 0) return false;
    return ::connect(sockfd_, (struct sockaddr*)&addr_, sizeof(addr_)) == 0;
}

bool TCPSocketStrategy::send(const char* data, int len) {
    int fd = clientfd_ != -1 ? clientfd_ : sockfd_;
    return ::send(fd, data, len, 0) == len;
}

int TCPSocketStrategy::receive(char* buffer, int len) {
    int fd = clientfd_ != -1 ? clientfd_ : sockfd_;
    return ::recv(fd, buffer, len, 0);
}

void TCPSocketStrategy::close() {
    if (clientfd_ != -1) ::close(clientfd_);
    if (sockfd_ != -1) ::close(sockfd_);
    clientfd_ = -1;
    sockfd_ = -1;
}

// 파일 이동됨. src/common/TCPSocketStrategy.cpp를 참조하세요.
