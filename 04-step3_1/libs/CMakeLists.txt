# 用 libmath.c 编译生成动态库 libmath
add_library(math SHARED libmath.c)

# 添加编译选项
target_compile_options(math PUBLIC -Wall)