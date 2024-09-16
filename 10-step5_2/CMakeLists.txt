# 规定项目所需的最低 cmake 版本为 3.1
cmake_minimum_required(VERSION 3.1)
# 定义项目名称和版本号
project(Step5 VERSION 1.0)

# 用 main.c 编译生成可执行文件 step2
add_executable(step5 main.c)
# 设置配置文件
configure_file(Config.h.in Config.h)
# 将 cmake 的顶层构建目录添加到 include 搜索路径
target_include_directories(step5 PRIVATE "${PROJECT_BINARY_DIR}")

# 添加子目录，执行子目录下的 CMakeLists.txt
add_subdirectory(libs)
# 将动态库 math 连接到目标文件 step5
target_link_libraries(step5 PRIVATE math)

# 安装
install(TARGETS step5 DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                    GROUP_READ
                    WORLD_READ
        )

# 测试
enable_testing()

# 如果没有参数，应该输出用法信息
add_test(NAME Usage COMMAND step5)
set_tests_properties(Usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:*")
# 如果参数不是数字，应该输出错误信息
add_test(NAME Error COMMAND step5 4abc)
set_tests_properties(Error PROPERTIES PASS_REGULAR_EXPRESSION "Error:*")
# 计算多个数字，判断是否正确
function(do_test target arg result)
  add_test(NAME Test_${arg} COMMAND ${target} ${arg})
  set_tests_properties(Test_${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

do_test(step5 4 "4.0* is 2.0*")
do_test(step5 9 "9.0* is 3.0*")
do_test(step5 35 "35.0* is 5.91*")
do_test(step5 100 "100.0* is 10.0*")
