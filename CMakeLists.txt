cmake_minimum_required(VERSION 3.30)
project(cpp_learn VERSION 1.0.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CLI11_PRECOMPILED ON)

if (WIN32)
    # 如果是 Windows 系统，设置控制台输出编码为 UTF-8
#    add_compile_definitions(_WIN32)
#    add_custom_command(TARGET acm PRE_BUILD
#            COMMAND chcp 65001 >nul
#            COMMENT "Setting console code page to UTF-8")
    # 静态链接所有库
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
elseif(APPLE)
    # 针对 macOS 系统的特定设置
    # 例如：设置 macOS 特定的编译选项或链接库
elseif(UNIX)
    # 针对 Linux 系统的特定设置
    # 例如：设置 Linux 特定的编译选项或链接库
endif()

add_executable(acm main.cpp acm.cpp)

include(FetchContent)

# cli11 依赖
FetchContent_Declare(
        cli11
        QUIET
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
        GIT_TAG 6c7b07a878ad834957b98d0f9ce1dbe0cb204fc9
        GIT_SHALLOW TRUE
)

FetchContent_MakeAvailable(cli11)

# 给项目代码链接依赖库
target_link_libraries(acm PRIVATE CLI11::CLI11)