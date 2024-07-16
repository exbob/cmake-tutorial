# 规定项目所需的最低 cmake 版本为 3.1
cmake_minimum_required(VERSION 3.1)

# 定义项目名称和版本号
project(HelloWorld VERSION 1.0)

# 设置目标文件及其依赖的源文件
add_executable(HelloWorld HelloWorld.c)

# 设置配置文件
configure_file(Config.h.in Config.h)

# 将 cmake 的顶层构建目录添加到 include 搜索路径
include_directories(${CMAKE_BINARY_DIR})
