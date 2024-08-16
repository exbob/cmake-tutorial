# Step4_1 输出调试信息

执行 cmake 时，首选会解析 CMakeLists.txt 文件，此时可以调用 [message()](https://cmake.org/cmake/help/latest/command/message.html) 命令打印一些变量的值，基本语法是：

```
message([<mode>] "message text" ...)
```

选项 mode 表示信息类型，类似日志级别，通常使用 `STATUS` ，它可以吧信息输出到 stdout 中，例如：

```
message(STATUS "\n")
message(STATUS "--------- Debug message --------")
message(STATUS "CMake Version is ${CMAKE_VERSION}")
message(STATUS "Binary directory is ${PROJECT_BINARY_DIR}")
message(STATUS "\n")
```

这里打印了两个 CMake 的变量：[CMAKE_VERSION](https://cmake.org/cmake/help/latest/variable/CMAKE_VERSION.html) 和 [PROJECT_BINARY_DIR](https://cmake.org/cmake/help/latest/variable/PROJECT_BINARY_DIR.html)。执行：

```
> cmake -S . -B build
-- The C compiler identification is GNU 9.4.0
-- The CXX compiler identification is GNU 9.4.0
-- Check for working C compiler: /usr/bin/cc
-- Check for working C compiler: /usr/bin/cc -- works
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Detecting C compile features
-- Detecting C compile features - done
-- Check for working CXX compiler: /usr/bin/c++
-- Check for working CXX compiler: /usr/bin/c++ -- works
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- 

-- --------- Debug message --------
-- CMake Version is 3.16.3
-- Binary directory is /home/lsc/workspace/cmake-tutorial/06-step4_1/build
-- 

-- Configuring done
-- Generating done
-- Build files have been written to: /home/lsc/workspace/cmake-tutorial/06-step4_1/build
```

可以看到，调试信息是在构建命令之前打印的，所以，构建过程中生成的信息，无法用 `message()` 命令输出。