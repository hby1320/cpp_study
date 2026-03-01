#pragma once
#include <cstring>
#include <unistd.h>
#include <common/ISocketStrategy.h>
#include <netinet/in.h>
#include <sys/socket.h>

class TCPSocketStrategy : public ISocketStrategy {
public:
    TCPSocketStrategy();
    ~TCPSocketStrategy() override;
    bool create() override;
    bool bind(int port) override;
    bool listen() override;
    bool accept() override;
    bool connect(const char* address, int port) override;
    bool send(const char* data, int len) override;
    int receive(char* buffer, int len) override;
    void close() override;
private:
    int sockfd_;
    int clientfd_;
    struct sockaddr_in addr_;
};
