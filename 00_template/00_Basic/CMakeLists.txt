# 规定项目所需的最低 cmake 版本为 3.15
cmake_minimum_required(VERSION 3.15)

# 可以在这里修改项目名称和版本号
project(Basic VERSION 1.0)

# 获得编译时间
string(TIMESTAMP BUILD_TIME "%Y.%m.%d %H:%M" UTC)
message(STATUS "Build Time: " ${BUILD_TIME})

# 用 main.c 编译生成可执行文件 basic，可以修改可执行文件的名称
set(program basic)
add_executable(${program} main.c)

# 设置配置文件
configure_file(Config.h.in Config.h)
# 将 cmake 的顶层构建目录添加到 include 搜索路径
target_include_directories(${program} PUBLIC "${PROJECT_BINARY_DIR}")

# 如果是 Debug 版本，就添加 __DEBUG__ 宏定义，添加 -Wall 编译选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Add Debug")
    target_compile_definitions(${program} PRIVATE "__DEBUG__")
    target_compile_options(${program} PRIVATE -Wall)
endif()