# Socket server and client sources
set(COMMON_SRCS
    core/src/common/TCPSocketStrategy.cpp
)
set(MANAGER_SRCS
    core/src/manager/SocketBuilder.cpp
    core/src/manager/StrategyFactory.cpp
)
set(SERVER_SRCS
    core/src/server/socket_server_class.cpp
)
set(CLIENT_SRCS
    core/src/server/socket_client_class.cpp
)

# include 루트로 core/include 디렉토리 추가
include_directories(${CMAKE_SOURCE_DIR}/core/include)

# 모듈별 include 디렉토리 등록
add_library(core_common INTERFACE)
target_include_directories(core_common INTERFACE ${CMAKE_SOURCE_DIR}/core/include/common)

add_library(core_manager INTERFACE)
target_include_directories(core_manager INTERFACE ${CMAKE_SOURCE_DIR}/core/include/manager)

# --------------------- target windows ----------------------
if(DEFINED PLATFORM_ID AND PLATFORM_ID STREQUAL "windows-x86_64-msvc")
    list(APPEND COMMON_SRCS core/src/common/WinsockStrategy.cpp)
    target_link_libraries(main_server PRIVATE Ws2_32)
    target_link_libraries(main_client PRIVATE Ws2_32)
endif()

# ---------------------- target linux ----------------------
# Not implemented yet, but can add Linux-specific sources if needed

# ---------------------- target darwin ----------------------
# Not implemented yet, but can add macOS-specific sources if needed

# ---------------------- target jetson thor ----------------------
# Not implemented yet, but can add Jetson-specific sources if needed

# executable targets create & linking
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
add_executable(main_server bin/main_server.cpp ${COMMON_SRCS} ${MANAGER_SRCS})
add_executable(main_client bin/main_client.cpp ${COMMON_SRCS} ${MANAGER_SRCS})

target_link_libraries(main_server PRIVATE core_common core_manager)
target_link_libraries(main_client PRIVATE core_common core_manager)

# include dirs
target_include_directories(main_server PRIVATE ${CMAKE_SOURCE_DIR}/core/include)
target_include_directories(main_client PRIVATE ${CMAKE_SOURCE_DIR}/core/include)

# core/src socket Server & Client target added
# Only add example server/client targets if their source files exist (avoid CMake errors)
if(EXISTS ${CMAKE_SOURCE_DIR}/core/src/server/socket_server_class.cpp)
    add_executable(socket_server_class ${CMAKE_SOURCE_DIR}/core/src/server/socket_server_class.cpp ${COMMON_SRCS})
    target_link_libraries(socket_server_class PRIVATE core_common core_manager)
    target_include_directories(socket_server_class PRIVATE ${CMAKE_SOURCE_DIR}/core/include)
endif()

if(EXISTS ${CMAKE_SOURCE_DIR}/core/src/server/socket_client_class.cpp)
    add_executable(socket_client_class ${CMAKE_SOURCE_DIR}/core/src/server/socket_client_class.cpp ${COMMON_SRCS})
    target_link_libraries(socket_client_class PRIVATE core_common core_manager)
    target_include_directories(socket_client_class PRIVATE ${CMAKE_SOURCE_DIR}/core/include)
endif()