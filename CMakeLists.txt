cmake_minimum_required(VERSION 3.14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ToolChins Platform
if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/toolchain/linux-x86_64.cmake)
    include(cmake/toolchain/linux-x86_64.cmake)
endif()
if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/toolchain/windows-x86_64-msvc.cmake)
    include(cmake/toolchain/windows-x86_64-msvc.cmake)
endif()
if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/toolchain/darwin-arm64.cmake)
    include(cmake/toolchain/darwin-arm64.cmake)
endif()
if(EXISTS ${CMAKE_SOURCE_DIR}/cmake/toolchain/jetson-thor-arm64.cmake)
    include(cmake/toolchain/jetson-thor-arm64.cmake)
endif()

project(cpp_study)

# Global variable define PLATFORM_DEFINE
if(DEFINED PLATFORM_DEFINE)
    message(STATUS "Applying platform define: ${PLATFORM_DEFINE}")
    add_compile_definitions(${PLATFORM_DEFINE})
endif()

# CMake Build opt setting
set(ENABLE_TEST OFF)
set(ENABLE_SocketServer ON)
set(ENABLE_Example ON)

# GTest
if (ENABLE_TEST)
    include(cmake/test.cmake)
endif()

# Socket server and client source
if (ENABLE_SocketServer)
    include(cmake/server.cmake)
endif ()





