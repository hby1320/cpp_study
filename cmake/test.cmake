# 테스트용 CMake 설정 (최적화 포함)
include(FetchContent)
# 다운로드 타임스탬프 정책 명시
set(FETCHCONTENT_DOWNLOADEXTRACT_TIMESTAMP TRUE)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/heads/main.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(socket_client_class_test
    ${CMAKE_SOURCE_DIR}/test/socket_client_class_test.cpp
    ${COMMON_SRCS}
    ${MANAGER_SRCS}
)

# 최적화 옵션
target_compile_options(socket_client_class_test PRIVATE -O2)

# 모듈 인터페이스 라이브러리를 통해 include 경로를 가져오게 함
target_link_libraries(socket_client_class_test PRIVATE gtest gtest_main core_common core_manager pthread)

add_test(NAME SocketClientClassTest COMMAND socket_client_class_test)
