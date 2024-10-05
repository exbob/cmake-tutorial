# 设置可执行文件的名称
set(program test)
# 新建一个可执行文件
add_executable(${program} test.c)

# 设置头文件搜索路径
target_include_directories(${program} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# 设置链接库搜索路径
target_link_directories(${program} PRIVATE ${PROJECT_BINARY_DIR}/output)
target_link_libraries(${program} PRIVATE ${LIB_NAME})

# 设置输出路径
set_target_properties(${program} PROPERTIES 
                        RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output # 设置可执行文件的输出路径
)

# 使能 ctest 测试
enable_testing()

# 如果没有参数，应该输出用法信息
add_test(NAME Usage COMMAND ${program})
set_tests_properties(Usage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:*")
# 如果参数不是数字，应该输出错误信息
add_test(NAME Error COMMAND ${program} 4abc)
set_tests_properties(Error PROPERTIES PASS_REGULAR_EXPRESSION "Error:*")
# 计算多个数字，判断是否正确
function(do_test target arg result)
  add_test(NAME Test_${arg} COMMAND ${target} ${arg})
  set_tests_properties(Test_${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()

do_test(${program} 4 "4.0* is 2.0*")
do_test(${program} 9 "9.0* is 3.0*")
do_test(${program} 35 "35.0* is 5.91*")
do_test(${program} 100 "100.0* is 10.0*")