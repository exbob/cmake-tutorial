# 规定项目所需的最低 cmake 版本为 3.1
cmake_minimum_required(VERSION 3.1)
# 定义项目名称和版本号
project(step12 VERSION 1.0)
# 定义生成的版本
# set(CMAKE_BUILD_TYPE Debug)
message(STATUS "CMAKE_BUILD_TYPE is ${CMAKE_BUILD_TYPE}")

# 用 main.c 编译生成可执行文件 step12
add_executable(step12 main.c)
# 设置配置文件
configure_file(Config.h.in Config.h)
# 将 cmake 的顶层构建目录添加到 include 搜索路径
target_include_directories(step12 PUBLIC "${PROJECT_BINARY_DIR}")

# 如果是 Debug 版本，就添加 __DEBUG__ 宏定义
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Add Debug")
    target_compile_definitions(step12 PRIVATE "__DEBUG__")
endif()