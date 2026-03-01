#include <manager/SocketBuilder.h>
#include <manager/StrategyFactory.h>
#include <common/TCPSocketStrategy.h>
#include <iostream>
#include <memory>
#include <cstdlib>

int main(int argc, char** argv) {
    const char* envp = std::getenv("CPP_STUDY_PORT");
    int port = 8080;
    if (envp) port = std::atoi(envp);
    if (argc > 1) port = std::atoi(argv[1]);

    std::cout << "[server] starting on port " << port << std::endl;
    SocketBuilder builder;
    auto strategy = manager::createDefaultStrategy();
    auto server = builder.setStrategy(strategy).build();

    std::cout << "[server] creating socket" << std::endl;
    if (!server->create()) {
        std::cerr << "[server] Socket create failed" << std::endl;
        return -1;
    }
    std::cout << "[server] socket created" << std::endl;

    std::cout << "[server] binding to port " << port << std::endl;
    if (!server->bind(port)) {
        std::cerr << "[server] Bind failed" << std::endl;
        return -1;
    }
    std::cout << "[server] bound" << std::endl;

    std::cout << "[server] listening" << std::endl;
    if (!server->listen()) {
        std::cerr << "[server] Listen failed" << std::endl;
        return -1;
    }
    std::cout << "[server] listening, waiting for accept" << std::endl;

    if (!server->accept()) {
        std::cerr << "[server] Accept failed" << std::endl;
        return -1;
    }
    std::cout << "[server] accepted connection" << std::endl;

    char buffer[1024] = {0};
    std::cout << "[server] receiving..." << std::endl;
    int r = server->receive(buffer, 1024);
    std::cout << "[server] receive returned: " << r << std::endl;
    std::cout << "[server] Message from client: " << buffer << std::endl;

    std::cout << "[server] sending reply" << std::endl;
    server->send("Hello from server", 18);
    std::cout << "[server] reply sent" << std::endl;

    server->close();
    std::cout << "[server] closed and exiting" << std::endl;
    return 0;
}
