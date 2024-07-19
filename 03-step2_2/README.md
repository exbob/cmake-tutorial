# Step2_2 使用条件选项

这个例子展示了使用条件选项来选择编译内容的方法。

## 编译

正常编译：

```
cmake -S . -B build
cd build
make
```

执行时不会打印调试信息：

```
> ./step2
Project Step2, Version 1.0
```

编译时设置 `DEBUG=ON` ，打开调试信息：

```
cmake -S . -B build -D DEBUG=ON
cd build
make
```

执行时可以打印出调试信息：

```
> ./step2
Project Step2, Version 1.0
/home/lsc/workspace/cmake-tutorial/03-step2_2/main.c[0014], main : debug message
```

## 解析

源文件结构很简单：

```
03-step2_2/
├── CMakeLists.txt
├── Config.h.in
├── README.md
└── main.c
```

在 `CMakeLists.txt` 中向 CMake 构建系统添加了一个 DEBUG 选项：

``` cmake
option(DEBUG "open or close log message" OFF)
```

[option()](https://cmake.org/cmake/help/latest/command/option.html) 命令用于定义一个布尔型变量，CMake 的布尔型变量可以接受以下值：

- 真值（True）：1，ON，YES，TRUE，Y，非零数字
- 假值（False）：0，OFF，NO，FALSE，N，IGNORE，NOTFOUND，空字符串，以 -NOTFOUND 结尾的字符串

而且不分大小写，`ON` 和 `no` 是同义词。如果没有赋值，默认是 `OFF` 。执行 cmake 命令时，可以用 `-D DEBUG=ON` 选项设为 `ON` 。下面的 [if()](https://cmake.org/cmake/help/latest/command/if.html) 语句会判断 `DEBUG` 的值：

``` cmake
if (DEBUG)
  target_compile_definitions(step2 PRIVATE __DEBUG__)
endif()
```

如果 `DEBUG` 为真，会执行 [target_compile_definitions()](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html) 命令，它告诉 CMake 构建系统，编译 `step2` 时，通过编译器定义一个 `__DEBUG__` 宏，执行 make 时显示详细的编译过程，可以看到编译时添加了 `-D__DEBUG__` 选项：

```
> VERBOSE=1 make
...
[ 50%] Building C object CMakeFiles/step2.dir/main.c.o
/usr/bin/cc -D__DEBUG__ -I/home/lsc/workspace/cmake-tutorial/03-step2_2/build   -o CMakeFiles/step2.dir/main.c.o   -c /home/lsc/workspace/cmake-tutorial/03-step2_2/main.c
```

这个选项预定义了 `__DEBUG__` 宏，`main.c` 的源码它来确定是否要打开调试信息：

``` C
#ifdef __DEBUG__
    #define pr_debug(format, ...) printf("%s[%04d], %s : "format"", __FILE__, __LINE__, __FUNCTION__, ##__VA_ARGS__)
#else
    #define pr_debug(format, ...)
#endif
```
