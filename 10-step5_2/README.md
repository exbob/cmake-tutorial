# Step5_2 测试

软件完成后，通常要进行单元测试，可以在 CMakeLists.txt 文件中调用 `enable_testing()` 和 `add_test()` 命令添加测试任务，然后执行 CMake 提供 ctest 程序，它会执行测试任务并报告结果。

## 执行

构建：

```
> cmake -S . -B build
> cmake --build build
> cd build
```

该程序的用法是接收一个参数，计算出它的平方跟：

```
> ./step5 
Project Step5, Version 1.0
Usage :
    ./step5 <number>
> ./step5  9
The square root of 9.000000 is 3.000000 .
```

需要测试各种参数下能否返回预期的结果。执行测试：

```
> ctest 
Test project /home/lsc/workspace/cmake-tutorial/10-step5_2/build
    Start 1: Usage
1/6 Test #1: Usage ............................   Passed    0.00 sec
    Start 2: Error
2/6 Test #2: Error ............................   Passed    0.00 sec
    Start 3: Test_4
3/6 Test #3: Test_4 ...........................   Passed    0.00 sec
    Start 4: Test_9
4/6 Test #4: Test_9 ...........................   Passed    0.00 sec
    Start 5: Test_35
5/6 Test #5: Test_35 ..........................   Passed    0.00 sec
    Start 6: Test_100
6/6 Test #6: Test_100 .........................   Passed    0.00 sec

100% tests passed, 0 tests failed out of 6

Total Test time (real) =   0.01 sec
```

这里依次执行了六项测试，如果测试通过就打印出 `Passed` ，如果失败会打印错误信息。最后汇总测试结果。

## 解析

在顶层 `CMakeLists.txt` 的尾部调用 [enable_testing()](https://cmake.org/cmake/help/latest/command/enable_testing.html) 使能测试，这样 cmake 才会将测试任务添加到构建系统里。

测试任务是调用 [add_test()](https://cmake.org/cmake/help/latest/command/add_test.html) 命令添加的，基本语法：

```
add_test(
    NAME <name>  # 添加一个名为 <name> 的测试任务，可以是任意字符串
    COMMAND <command> [<arg>...]  # 测试任务要执行的程序和参数
    [CONFIGURATIONS <config>...]
    [WORKING_DIRECTORY <dir>]
    [COMMAND_EXPAND_LISTS])
```

用 [set_tests_properties()](https://cmake.org/cmake/help/latest/command/set_tests_properties.html) 为测试任务添加属性。

```
set_tests_properties(
    <tests>...   # add_test() 添加的测试任务的名字，可以同时设置多个。
    PROPERTIES <prop1> <value1> [<prop2> <value2>]...   # 可以设置多个属性
    )
```

可以设置的属性参考 [Properties on Tests](https://cmake.org/cmake/help/latest/manual/cmake-properties.7.html#test-properties)，常用的是 `PASS_REGULAR_EXPRESSION` ，测试输出（stdout或stderr）内容是否匹配这里设定的正则表达式。例如：

```
add_test(NAME Error COMMAND step5 4abc)
set_tests_properties(Error PROPERTIES PASS_REGULAR_EXPRESSION "Error:*")
```

这定义了一个名为 Error 的错误任务，它会执行 `step5 4abc` , `step5` 的参数应该是数字，`4abc` 是错误的参数，执行后应该打印错误信息。

如果执行多个同类测试，可以定义一个函数，例如：

```
function(do_test target arg result)
  add_test(NAME Test_${arg} COMMAND ${target} ${arg})
  set_tests_properties(Test_${arg}
    PROPERTIES PASS_REGULAR_EXPRESSION ${result}
    )
endfunction()
```

定义了一个名为 `do_test` 的函数，可以接收三个参数，分别是：可以执行程序，可执行程序的参数，应该返回的结果。然后可以调用 `do_test()` 测试不通的参数：

```
do_test(step5 4 "4.0* is 2.0*")
do_test(step5 9 "9.0* is 3.0*")
do_test(step5 35 "35.0* is 5.91*")
do_test(step5 100 "100.0* is 10.0*")
```
