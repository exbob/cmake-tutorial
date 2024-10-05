# 规定项目所需的最低 cmake 版本为 3.15
cmake_minimum_required(VERSION 3.15)

# 可以在这里修改项目名称和版本号
project(demo VERSION 1.0)

# 用 main.c 编译生成可执行文件 basic，可以修改可执行文件的名称
set(program demo)

# 生成可执行文件
add_executable(${program} main.c)

# 将 cmake 的顶层构建目录添加到 include 搜索路径
target_include_directories(${program} PUBLIC "${PROJECT_BINARY_DIR}")
# 链接 math 库
target_link_libraries(${program} PRIVATE math)
