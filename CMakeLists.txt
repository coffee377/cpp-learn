cmake_minimum_required(VERSION 3.30)
project(cpp_learn)

set(CMAKE_CXX_STANDARD 23)
set(CLI11_PRECOMPILED ON)
# 静态链接所有库
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")

add_executable(acm main.cpp
        acm.cpp
        acm.hpp)

include(FetchContent)

# cli11 依赖
FetchContent_Declare(
        cli11
        QUIET
        GIT_REPOSITORY https://github.com/CLIUtils/CLI11.git
        GIT_TAG 6c7b07a878ad834957b98d0f9ce1dbe0cb204fc9
        GIT_SHALLOW TRUE
)

# cxxopts 依赖
#FetchContent_Declare(
#        cxxopts
#        GIT_REPOSITORY https://github.com/jarro2783/cxxopts
#        GIT_TAG v3.2.1
#        GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(cli11)

# 给项目代码链接依赖库
target_link_libraries(acm PRIVATE CLI11::CLI11)