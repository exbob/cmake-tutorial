# Step3_1 目标的属性

从 CMake 3.x 开始，CMakeLists.txt 的核心是描述目标文件（`add_executable()` 和 `add_library()` 命令创建的文件）的构建过程。这个过程中，每个目标都需要一组属性，例如需要链接的其他目标文件，编译选项，头文件和链接库的搜索路径等，这些属性都存储在特殊的 CMake 变量中，并由构建系统自动使用。我们可以调用一些命令设置这些属性。常用的包括：

- [target_compile_definitions()](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html)，向目标文件传递预处理宏定义。
- [target_compile_options()](https://cmake.org/cmake/help/latest/command/target_compile_options.html)，添加编译目标文件时的编译选项。
- [target_include_directories()](https://cmake.org/cmake/help/latest/command/target_include_directories.html)，目标文件包含的头文件的搜索路径。
- [target_link_directories()](https://cmake.org/cmake/help/latest/command/target_link_directories.html)，目标需要的链接库的搜索路径。
- [target_link_options()](https://cmake.org/cmake/help/latest/command/target_link_options.html)，添加链接标志。
- [target_sources()](https://cmake.org/cmake/help/latest/command/target_sources.html)，设置编译目标时使用的源文件。

每个属性都可以用如下三个关键字之一控制属性的传递（或者叫做继承）范围：

- PRIVATE，属性仅供该目标使用。
- PUBLIC，属性既可供该目标使用，也可供与其链接的其他目标使用。
- INTERFACE，属性仅与其链接的其他目标使用，该目标并不使用。

总结如下：

| 权限/特性 | PRIVATE | PUBLIC | INTERFACE
| -------- | -------- | ------ | ---------
| 目标自身使用 | ✅ | ✅ | ❌
| 传递给其他目标 | ❌ | ✅ | ✅
| 目标自身不使用但传递 | ❌ | ❌ | ✅


以 `target_compile_options()` 为例，在 `./libs/CMakeLists.txt` 文件中，为 `libmath` 添加一个编译选项 `-Wall` ，传递范围设为 `PUBLIC` ：

```
target_compile_options(math PUBLIC -Wall)
```

生成 MakeFile ：

```
> cmake -S . -B build
> cd build
```

本例中添加了两个目标：`step3` 和 `libmath` ，动态库 `libmath` 需要链接到可执行文件 `step3` 。编译时可以看到，两个目标文件编译时都使用了 `-Wall` 选项:

```
> VERBOSE=1 make | grep Wall
cd /home/lsc/workspace/cmake-tutorial/04-step3_1/build/libs && /usr/bin/cc -Dmath_EXPORTS  -fPIC   -Wall -o CMakeFiles/math.dir/libmath.c.o   -c /home/lsc/workspace/cmake-tutorial/04-step3_1/libs/libmath.c
/usr/bin/cc  -I/home/lsc/workspace/cmake-tutorial/04-step3_1/build  -Wall -o CMakeFiles/step3.dir/main.c.o   -c /home/lsc/workspace/cmake-tutorial/04-step3_1/main.c
```

将传递范围设为 `PRIVATE` :

```
target_compile_options(math PRIVATE -Wall)
```

重新生成 MakeFile，并编译。可以看到，只有编译生成动态库 `libmath` 时使用了 `-Wall` 选项：

```
> VERBOSE=1 make | grep Wall
cd /home/lsc/workspace/cmake-tutorial/04-step3_1/build/libs && /usr/bin/cc -Dmath_EXPORTS  -fPIC   -Wall -o CMakeFiles/math.dir/libmath.c.o   -c /home/lsc/workspace/cmake-tutorial/04-step3_1/libs/libmath.c
```

将传递范围设为 `INTERFACE` :

```
target_compile_options(math INTERFACE -Wall)
```

重新生成 MakeFile，并编译。可以看到，只有编译可以执行文件 `step3` 的源文件 `main.c` 时使用了 `-Wall` 选项：

```
> VERBOSE=1 make | grep Wall
/usr/bin/cc  -I/home/lsc/workspace/cmake-tutorial/04-step3_1/build  -Wall -o CMakeFiles/step3.dir/main.c.o   -c /home/lsc/workspace/cmake-tutorial/04-step3_1/main.c
```

参考：

- <https://leimao.github.io/blog/CMake-Public-Private-Interface/>
- <https://kubasejdak.com/modern-cmake-is-like-inheritance>
- <https://juejin.cn/post/7293728293769347107>
- <https://chunleili.github.io/cmake/understanding-INTERFACE>