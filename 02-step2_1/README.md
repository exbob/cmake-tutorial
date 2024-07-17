# Step2 添加动态库

这个例子展示了在 CMake 项目中添加并使用动态链接库的方法。

## 编译

编译：

```
cmake -S . -B build
cd build
make
```

执行：

```
> ./step2
Project Step2, Version 1.0
The square root of 4.000000 is 2.000000 .
```

## 解析

源文件结构如下：

```
02-step2_1/
├── CMakeLists.txt
├── Config.h.in
├── README.md
├── libs
│   ├── CMakeLists.txt
│   ├── libmath.c
│   └── libmath.h
└── main.c
```

程序功能很简单，子目录 `libs` 下的 `libmath.c` 定义了 `mysqrt()` 函数，用于计算一个浮点数的平方根，通过动态链接库的方式供其他函数调用，`main.c` 使用 `libs/libmath.h` 头文件调用 `mysqrt()` 执行计算。

子目录的 `CMakeLists.txt` 使用 [add_library()](https://cmake.org/cmake/help/latest/command/add_library.html) 命令描述链接库的生成过程：

```
add_library(math SHARED libmath.c)
```

它表示用源文件 `libmath.c` 生成动态库文件 `libmath.so` 。

- 中间参数 `SHARED` 表示要生成动态库，如果要生成静态库，可以设置为 `STATIC` 。
- 第一个参数是库的逻辑名称，必须在项目中全局唯一，构建的时候，cmake 会根据当前的平台类型生成实际的文件名，这里是 Linux 系统，所以生成的库文件是 libmath.so 。
- 最后设置依赖的源文件，如果是多个源文件，用空格隔开。 

上层 `CMakeLists.txt` 使用 [add_subdirectory()](https://cmake.org/cmake/help/latest/command/add_subdirectory.html) 命令添加子目录，然后使用 [target_link_libraries()](https://cmake.org/cmake/help/latest/command/target_link_libraries.html) 命令描述链接关系：

```
target_link_libraries(step2 PUBLIC math)
```

它的作用是把指定库（math）连接到指定的目标文件（step2）上。`step2` 是 `main.c` 生成的可执行程序，`math` 是子目录中的动态库名称。中间的 `PUBLIC` 是控制传递属性的参数。

这里还用到了 `PROJECT_BINARY_DIR` 变量，它指向目标文件输出的路径，通常就是执行 cmake 命令时的路径。还有一个表示源码路径的变量 `PROJECT_SOURCE_DIR` ，它们的值都是由 `project()` 命令自动设置的。