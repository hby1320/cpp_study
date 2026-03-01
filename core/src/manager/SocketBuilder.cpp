#include <manager/SocketBuilder.h>

SocketBuilder& SocketBuilder::setStrategy(std::shared_ptr<ISocketStrategy> strategy) {
    strategy_ = strategy;
    return *this;
}

std::shared_ptr<ISocketStrategy> SocketBuilder::build() {
    return strategy_;
}
