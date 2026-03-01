#pragma once

#include <memory>
#include <common/ISocketStrategy.h>

namespace manager {

// 플랫폼/환경에 맞는 기본 ISocketStrategy 인스턴스를 반환합니다.
// 구현은 compile-time 매크로(툴체인에서 정의된 PLATFORM_DEFINE)로 분기합니다.
std::shared_ptr<ISocketStrategy> createDefaultStrategy();

} // namespace manager
