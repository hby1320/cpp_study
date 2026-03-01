#include <gtest/gtest.h>
#include <manager/SocketBuilder.h>
#include <common/TCPSocketStrategy.h>
#include <memory>

TEST(SocketClientClassTest, CreateAndConnect) {
    SocketBuilder builder;
    auto strategy = std::make_shared<TCPSocketStrategy>();
    auto client = builder.setStrategy(strategy).build();
    EXPECT_TRUE(client->create());
    // 서버가 실행 중일 때만 성공
    EXPECT_TRUE(client->connect("127.0.0.1", 8080));
    client->close();
}

TEST(SocketClientClassTest, SendAndReceive) {
    SocketBuilder builder;
    auto strategy = std::make_shared<TCPSocketStrategy>();
    auto client = builder.setStrategy(strategy).build();
    client->create();
    client->connect("127.0.0.1", 8080);
    EXPECT_TRUE(client->send("Hello from client", 18));
    char buffer[1024] = {0};
    int received = client->receive(buffer, 1024);
    EXPECT_GT(received, 0);
    client->close();
}
