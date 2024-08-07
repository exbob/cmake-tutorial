# 用 libmath.c 编译生成动态库 libmath
add_library(math SHARED libmath.c)

# 链接 libmath 的目标文件都需要包含当前的源码目录
target_include_directories(math INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
