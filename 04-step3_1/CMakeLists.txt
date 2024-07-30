# 规定项目所需的最低 cmake 版本为 3.1
cmake_minimum_required(VERSION 3.1)
# 定义项目名称和版本号
project(Step3 VERSION 1.0)

# 用 main.c 编译生成可执行文件 step2
add_executable(step3 main.c)
# 设置配置文件
configure_file(Config.h.in Config.h)
# 将 cmake 的顶层构建目录添加到 include 搜索路径
target_include_directories(step3 PUBLIC "${PROJECT_BINARY_DIR}")

# 添加子目录，执行子目录下的 CMakeLists.txt
add_subdirectory(libs)
# 将动态库 libmath 链接到目标文件 step3
target_link_libraries(step3 PUBLIC math)
