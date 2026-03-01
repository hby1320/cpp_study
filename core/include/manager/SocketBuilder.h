#pragma once
#include <common/ISocketStrategy.h>
#include <memory>

class SocketBuilder {
public:
    SocketBuilder& setStrategy(std::shared_ptr<ISocketStrategy> strategy);
    std::shared_ptr<ISocketStrategy> build();
private:
    std::shared_ptr<ISocketStrategy> strategy_;
};
