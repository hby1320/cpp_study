#pragma once

/*
  TCPSocketStrategy
  - TCP 소켓을 POSIX 계열(Unix/Linux/macOS)에서 동작하도록 구현한 기본 전략입니다.
  - 플랫폼별 차이가 필요한 경우(예: Windows의 Winsock 초기화, Jetson 특화 네트워크 옵션 등)
    이 파일의 구현부나 별도의 전략 클래스를 만들어 #ifdef PLATFORM_xxx를 사용해 분기할 수 있습니다.
  - 권장 패턴: 플랫폼 전용 최적화는 구현(.cpp) 내부에서 #ifdef로 분리하고, 헤더는 인터페이스만 노출하세요.
*/

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
    bool connect(const char *address, int port) override;
    bool send(const char *data, int len) override;
    int receive(char *buffer, int len) override;
    void close() override;

  private:
    int sockfd_;
    int clientfd_;
    struct sockaddr_in addr_;
};
