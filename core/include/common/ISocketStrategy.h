#pragma once

/*
@doc ISocketStrategy
@details
  - 목적: 네트워크 소켓의 플랫폼/프로토콜별 구현을 추상화하기 위한 전략 인터페이스입니다.
  - 사용법: 플랫폼(또는 빌드 툴체인)별로 `TCPSocketStrategy`, `UnixDomainSocketStrategy` 등
    구체 전략을 구현하고, 팩토리(`manager/StrategyFactory`)를 통해 런타임/빌드타임에
    적절한 전략을 얻어 사용합니다.
*/

class ISocketStrategy {
public:
    virtual ~ISocketStrategy() = default;
    virtual bool create() = 0;
    virtual bool bind(int port) = 0;
    virtual bool listen() = 0;
    virtual bool accept() = 0;
    virtual bool connect(const char* address, int port) = 0;
    virtual bool send(const char* data, int len) = 0;
    virtual int receive(char* buffer, int len) = 0;
    virtual void close() = 0;
};
