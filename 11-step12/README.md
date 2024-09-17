# Step12 使用 CMAKE_BUILD_TYPE

对于一个 C/C++ 程序来说，通常要编译生成 Debug 和 Release 两种版本：

- Debug 版本（调试版本）：包含调试信息，所以容量比 Release 大很多，并且不进行任何优化（优化会使调试复杂化，因为源代码和生成的指令间关系会更复杂），便于程序员调试。
- Release 版本（发布版本）：不对源代码进行调试，编译时对应用程序的速度进行优化，使得程序在代码大小和运行速度上都是最优的。

为此，CMake 提供了 [Build Configurations](https://cmake.org/cmake/help/latest/manual/cmake-buildsystem.7.html#build-configurations) 支持，可以选择生成对应的版本，核心是 [CMAKE_BUILD_TYPE](https://cmake.org/cmake/help/latest/variable/CMAKE_BUILD_TYPE.html#variable:CMAKE_BUILD_TYPE) 变量，默认值是空字符串：

```
> cmake --system-information | grep CMAKE_BUILD_TYPE
CMAKE_BUILD_TYPE == ""
CMAKE_BUILD_TYPE ""
```

系统提供了四个可选值，取值会影响编译和链接时的选项:
- Debug，构建一个调试版本，启用了调试信息，并且通常关闭了优化。
- Release，构建一个发布版本，关闭了调试信息，启动了各种优化选项。
- RelWithDebInfo，类似 Release ，但是包含了部分调试信息。
- MinSizeRel，构建最小的可执行文件，因此关闭了大部分调试和优化选项。

设定一个值后，cmake 会将对应的 `CMAKE_<LANG>_FLAGS_<CONFIG>` 变量的值添加到编译选项中。其中，`<LANG>` 匹配语言类型（例如 C 和 CXX），`<CONFIG>` 匹配 `CMAKE_BUILD_TYPE` 的值，例如，`CMAKE_C_FLAGS_DEBUG` 变量的默认值是 `-g` ：

```
> cmake --system-information | grep CMAKE_C_FLAGS_DEBUG
CMAKE_C_FLAGS_DEBUG == "-g"
CMAKE_C_FLAGS_DEBUG "-g"
CMAKE_C_FLAGS_DEBUG_INIT " -g"
```

如果将 `CMAKE_BUILD_TYPE` 设置为 `Debug`，就会把编译选项 `-g` 传递给编译器，例如在 CMakeLists.txt 中添加 `set(CMAKE_BUILD_TYPE Debug)` 命令，然后查看编译参数：

```
> VERBOSE=1 make | grep cc
/usr/bin/cc -D__DEBUG__ -I/home/lsc/workspace/cmake-tutorial/11-step12/Debug  -g   -o CMakeFiles/step12.dir/main.c.o   -c /home/lsc/workspace/cmake-tutorial/11-step12/main.c
/usr/bin/cc -g  -rdynamic CMakeFiles/step12.dir/main.c.o  -o step12
```

另一种方法是在执行 cmake 命令时，用 `-D` 选项设置，例如，生成 Debug 版本：

```
> cmake -S . -B Debug -DCMAKE_BUILD_TYPE=Debug
> cmake --build Debug
> ./Debug/step12
Project step12, Version 1.0
/home/lsc/workspace/cmake-tutorial/11-step12/main.c[0014], main : debug message
```

生成 Release 版本：

```
> cmake -S . -B Release -DCMAKE_BUILD_TYPE=Release
> cmake --build Release
> ./Release/step12 
Project step12, Version 1.0
```