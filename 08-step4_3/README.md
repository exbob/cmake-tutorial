# Step4_3 使用生成器表达式

cmake 的执行过程分为三个阶段：

1. Configure，CMake 将解析源代码树的顶层 CMakeLists.txt，并创建一个包含缓存变量的 CMakeCache.txt 文件，完成后提示 Configuring done 。
2. Generate，CMake 将使用来自 CMakeLists.txt 的信息和来自 CMakeCache.txt 的变量生成构建所需的工具文件，完成后提示 Generating done 。
3. Build，在这一步中，您的项目目标将被编译链接，构建出目标文件。可以执行 `cmake --build` 命令，或者执行 `make` 。

大致如下：

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
-- Configuring done
-- Generating done
-- Build files have been written to: /home/lsc/workspace/cmake-tutorial/08-step4_3/build

> cmake --build build
Scanning dependencies of target step4
[ 50%] Building C object CMakeFiles/step4.dir/main.c.o
[100%] Linking C executable step4
[100%] Built target step4

> ./build/step4 
Project Step4, Version 1.0
```

[生成器表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html)是在 Generate 阶段才会展开执行的一种语句，基本语法是 `$<...>` ，支持嵌套，cmake 会执行括号内的语句，返回一个值，主要用途是根据条件设置编译、链接和安装等各种属性。例如，下面这条语句表示 1.0 以上的版本才会加上 `-Wall` 编译选项：

```
target_compile_options(step4 PRIVATE $<$<VERSION_GREATER:${PROJECT_VERSION},1.0>:-Wall>)
```

这里用到了两种生成器表达式：

1. 内层的 `$<VERSION_GREATER:${PROJECT_VERSION},1.0>` 是[版本比较器](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#version-comparisons)，如果版本大于 1.0 就返回 1 ，否则返回 0 。
2. 外层是基本的[条件表达式](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#conditional-expressions)，如果条件是 1 就返回字符串 `-Wall` ，否则返回空字符串。

如果设置了 `project(Step4 VERSION 1.1)` ，将版本号改为 1.1 ，编译时就可以看到 `-Wall` 选项：

```
> VERBOSE=1 make | grep cc
/usr/bin/cc  -I/home/lsc/workspace/cmake-tutorial/08-step4_3/build  -Wall -o CMakeFiles/step4.dir/main.c.o   -c /home/lsc/workspace/cmake-tutorial/08-step4_3/main.c
/usr/bin/cc   -rdynamic CMakeFiles/step4.dir/main.c.o  -o step4
> ./step4 
Project Step4, Version 1.1
```

如果要大于这个表达式的值，可以用 `file()` 命令，因为这条语句只在 Generate 阶段展开执行。