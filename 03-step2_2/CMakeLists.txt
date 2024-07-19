# 规定项目所需的最低 cmake 版本为 3.1
cmake_minimum_required(VERSION 3.1)
# 定义项目名称和版本号
project(Step2 VERSION 1.0)

# 用 main.c 编译生成可执行文件 step2
add_executable(step2 main.c)
# 设置配置文件
configure_file(Config.h.in Config.h)
# 将 cmake 的顶层构建目录添加到 include 搜索路径
target_include_directories(step2 PUBLIC "${PROJECT_BINARY_DIR}")

# 新建一个名为 DEBUG 的选项，初始值是 OFF
option(DEBUG "open or close log message" OFF)
# 如果 DEBUG 变量为真，编译目标文件时会预定义 __DEBUG__ 宏
if (DEBUG)
  target_compile_definitions(step2 PRIVATE __DEBUG__)
endif()