#include <manager/StrategyFactory.h>
#include <common/TCPSocketStrategy.h>
#include <common/WinsockStrategy.h>

namespace manager {

std::shared_ptr<ISocketStrategy> createDefaultStrategy() {
    // 기본적으로는 TCP 전략을 반환합니다. 필요시 플랫폼별 커스텀 전략을 추가하세요.
#ifdef PLATFORM_DARWIN_ARM64
    // macOS(arm64) 전용 전략(현재는 TCPSocketStrategy 사용)
    return std::make_shared<TCPSocketStrategy>();
#elif defined(PLATFORM_LINUX_X86_64)
    // Ubuntu x86_64 전용 전략
    return std::make_shared<TCPSocketStrategy>();
#elif defined(PLATFORM_WINDOWS_X86_64_MSVC)
    // Windows MSVC용 (추후 Winsock 기반 구현으로 교체 가능)
    return std::make_shared<WinsockStrategy>();
#elif defined(PLATFORM_JETSON_THOR_ARM64)
    // JetsonThor 특화 전략(추후 성능/옵션 최적화 구현)
    return std::make_shared<TCPSocketStrategy>();
#else
    // 알 수 없는 플랫폼: 안전하게 기본 TCP 전략 사용
    return std::make_shared<TCPSocketStrategy>();
#endif
}

} // namespace manager
