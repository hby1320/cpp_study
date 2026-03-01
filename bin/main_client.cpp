#include <manager/SocketBuilder.h>
#include <manager/StrategyFactory.h>
#include <common/TCPSocketStrategy.h>
#include <iostream>
#include <memory>

int main() {
    std::cout << "[client] starting" << std::endl;
    SocketBuilder builder;
    auto strategy = manager::createDefaultStrategy();
    auto client = builder.setStrategy(strategy).build();

    std::cout << "[client] creating socket" << std::endl;
    if (!client->create()) {
        std::cerr << "[client] Socket create failed" << std::endl;
        return -1;
    }
    std::cout << "[client] socket created" << std::endl;

    std::cout << "[client] connecting to 127.0.0.1:8080" << std::endl;
    if (!client->connect("127.0.0.1", 8080)) {
        std::cerr << "[client] Connect failed" << std::endl;
        return -1;
    }
    std::cout << "[client] connected" << std::endl;

    std::cout << "[client] sending message" << std::endl;
    client->send("Hello from client", 18);
    std::cout << "[client] sent, waiting for reply" << std::endl;

    char buffer[1024] = {0};
    int r = client->receive(buffer, 1024);
    std::cout << "[client] receive returned: " << r << std::endl;
    std::cout << "[client] Message from server: " << buffer << std::endl;

    client->close();
    std::cout << "[client] closed and exiting" << std::endl;
    return 0;
}
