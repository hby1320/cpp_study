#pragma once

#include <common/ISocketStrategy.h>

/*
 WinsockStrategy
 - Windows 전용 Winsock 기반 소켓 구현입니다.
 - 이 프로젝트에서는 툴체인 매크로(`PLATFORM_WINDOWS_X86_64_MSVC`)에 따라 팩토리가 이 구현을 반환합니다.
 - 비윈도우 플랫폼에서는 호출되면 실패를 반환하거나 대체 구현을 사용하도록 팩토리를 구성하세요.
*/

class WinsockStrategy : public ISocketStrategy {
public:
    WinsockStrategy();
    ~WinsockStrategy() override;

    bool create() override;
    bool bind(int port) override;
    bool listen() override;
    bool accept() override;
    bool connect(const char* address, int port) override;
    bool send(const char* data, int len) override;
    int receive(char* buffer, int len) override;
    void close() override;

private:
#ifdef _WIN32
    SOCKET sock_;
    SOCKET client_;
    WSADATA wsaData_;
#else
    int sock_ = -1;
    int client_ = -1;
#endif
};

