#include <common/TCPSocketStrategy.h>
#include <iostream>
#include <arpa/inet.h>
#include <cerrno>
#include <cstring>
#include <sys/select.h>

TCPSocketStrategy::TCPSocketStrategy() : sockfd_(-1), clientfd_(-1) {
    memset(&addr_, 0, sizeof(addr_));
}

TCPSocketStrategy::~TCPSocketStrategy() {
    close();
}

bool TCPSocketStrategy::create() {
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd_ == -1) {
        std::cerr << "socket() failed: " << std::strerror(errno) << std::endl;
        return false;
    }
    // 주소 재사용 옵션
    int opt = 1;
    if (setsockopt(sockfd_, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) != 0) {
        std::cerr << "setsockopt(SO_REUSEADDR) failed: " << std::strerror(errno) << std::endl;
    }
#ifdef SO_REUSEPORT
    if (setsockopt(sockfd_, SOL_SOCKET, SO_REUSEPORT, &opt, sizeof(opt)) != 0) {
        // not critical
        std::cerr << "setsockopt(SO_REUSEPORT) failed: " << std::strerror(errno) << std::endl;
    }
#endif
    return true;
}

bool TCPSocketStrategy::bind(int port) {
    addr_.sin_family = AF_INET;
    addr_.sin_addr.s_addr = INADDR_ANY;
    addr_.sin_port = htons(port);
    if (::bind(sockfd_, (struct sockaddr*)&addr_, sizeof(addr_)) != 0) {
        std::cerr << "bind() failed: " << std::strerror(errno) << std::endl;
        return false;
    }
    return true;
}

bool TCPSocketStrategy::listen() {
    return ::listen(sockfd_, 3) == 0;
}

bool TCPSocketStrategy::accept() {
    // Wait with timeout using select to avoid indefinite blocking in tests
    fd_set readfds;
    FD_ZERO(&readfds);
    FD_SET(sockfd_, &readfds);
    struct timeval tv;
    tv.tv_sec = 10; // 10s timeout
    tv.tv_usec = 0;
    int rv = select(sockfd_ + 1, &readfds, NULL, NULL, &tv);
    if (rv == 0) {
        std::cerr << "accept() timeout waiting for connection" << std::endl;
        return false;
    }
    if (rv < 0) {
        std::cerr << "select() failed: " << std::strerror(errno) << std::endl;
        return false;
    }
    socklen_t addrlen = sizeof(addr_);
    clientfd_ = ::accept(sockfd_, (struct sockaddr*)&addr_, &addrlen);
    if (clientfd_ == -1) {
        std::cerr << "accept() failed: " << std::strerror(errno) << std::endl;
        return false;
    }
    // set recv timeout on accepted socket to avoid indefinite recv block
    struct timeval rtv;
    rtv.tv_sec = 5; // 5s
    rtv.tv_usec = 0;
    if (setsockopt(clientfd_, SOL_SOCKET, SO_RCVTIMEO, &rtv, sizeof(rtv)) != 0) {
        std::cerr << "setsockopt(SO_RCVTIMEO) failed: " << std::strerror(errno) << std::endl;
    }
    return true;
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
    int r = ::recv(fd, buffer, len, 0);
    if (r < 0 && (errno == EWOULDBLOCK || errno == EAGAIN)) {
        // timeout
        return 0;
    }
    return r;
}

void TCPSocketStrategy::close() {
    if (clientfd_ != -1) ::close(clientfd_);
    if (sockfd_ != -1) ::close(sockfd_);
    clientfd_ = -1;
    sockfd_ = -1;
}
