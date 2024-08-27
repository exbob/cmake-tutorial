# 规定项目所需的最低 cmake 版本为 3.1
cmake_minimum_required(VERSION 3.1)
# 定义项目名称和版本号
project(Step4 VERSION 1.0)

# 用 main.c 编译生成可执行文件 step4
add_executable(step4 main.c)
# 设置配置文件
configure_file(Config.h.in Config.h)
# 将 cmake 的顶层构建目录添加到 include 搜索路径
target_include_directories(step4 PUBLIC "${PROJECT_BINARY_DIR}")

# 大于 1.0 的版本才会加上 -Wall 编译选项
target_compile_options(step4 PRIVATE $<$<VERSION_GREATER:${PROJECT_VERSION},1.0>:-Wall>)
# 打印调试信息
# file(GENERATE OUTPUT debug.log CONTENT "$<$<VERSION_GREATER:${PROJECT_VERSION},1.0>:-Wall>")