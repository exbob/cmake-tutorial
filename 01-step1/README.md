# Step1 基本工程

## 编译

这是一个最简单的 cmake 工程。可以在当前目录直接执行 `cmake .` 生成 Makefile，但是 cmake 没有 clean 命令，其生成的大量文件与源文件混在一起，很难清除。更推荐如下命令，将生成的文件放到 build 文件夹下：

```
cmake -S . -B build
```

- -S 设置了源码路径，就是当前目录。
- -B 设置了生成文件的路径，会新建一个 build 文件夹。

然后进入 build 编译并执行：

```
$ cd build
$ make
$ ./HelloWorld
Hello World!
Version is 1.0
```

## 解析

源码结构如下：

```
01-step1/
├── CMakeLists.txt
├── Config.h.in
├── HelloWorld.c
├── Makefile
└── README.md
```

`CMakeLists.txt` 是 cmake 生成 Makefile 所依赖的描述性文件，文件内容由一行一行的命令组成，命令名称不区分大小写，通过括号传递参数，多个参数通过空格分隔，该文件内容只有五行：

```
cmake_minimum_required(VERSION 3.1)
project(HelloWorld VERSION 1.0)
add_executable(HelloWorld HelloWorld.c)
configure_file(Config.h.in Config.h)
include_directories(${CMAKE_BINARY_DIR})
```

任何 CMake 项目的最上层 CMakeLists.txt 文件必须使用 [cmake_minimum_required()](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html#command:cmake_minimum_required) 命令来指定最低 CMake 版本。这样可以确保后续的 CMake 函数在兼容的 CMake 版本下运行。

在 `cmake_minimum_required()` 之后，必须使用 [project()](https://cmake.org/cmake/help/latest/command/project.html#command:project) 命令设置项目名称，它的语法是：

```
project(<PROJECT-NAME>
        [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
        [DESCRIPTION <project-description-string>]
        [HOMEPAGE_URL <url-string>]
        [LANGUAGES <language-name>...])
```

第一个参数设置项目名称，设置后可以用 `PROJECT_NAME` 变量引用。后面还可以设置版本号和描述等。VERSION 参数用于设置版本号，版本号的格式是点分多个整数，这样添加的版本号可以通过特定变量引用：

* `PROJECT_VERSION` 或者 `<PROJECT-NAME>_VERSION` ，存放完整的版本号 。
* `PROJECT_VERSION_MAJOR` 或者 `<PROJECT-NAME>_VERSION_MAJOR` ，存放 major 。
* `PROJECT_VERSION_MINOR` 或者 `<PROJECT-NAME>_VERSION_MINOR` ，存放 minor 。
* `PROJECT_VERSION_PATCH` 或者 `<PROJECT-NAME>_VERSION_PATCH` ， 存放 patch 。
* `PROJECT_VERSION_TWEAK` 或者 `<PROJECT-NAME>_VERSION_TWEAK` ，存放 tweak 。

例如，我们在 `Config.h.in` 文件中引用：

``` C
#define VERSION "@HelloWorld_VERSION@"
```

执行到 `configure_file(Config.h.in Config.h)` 命令时，cmake 会读取这个文件，并替换其中的变量生成 `Config.h` 文件。因为`Config.h` 文件会生成在 build 目录下，需要用 [include_directories()](https://cmake.org/cmake/help/latest/command/include_directories.html) 命令这个目录天添加到 include 搜索路径里，否则编译时会找不到头文件。`${CMAKE_BINARY_DIR}` 变量是一个全局变量，表示顶层构建目录(build)的绝对路径。`include_directories()` 命令属于全局设置，影响所有目标，适合简单项目。对于复杂项目，推荐使用 
[target_include_directories()](https://cmake.org/cmake/help/latest/command/target_include_directories.html)，可以针对特定目标设置 include 搜索路径。

第三行 [add_executable()](https://cmake.org/cmake/help/latest/command/add_executable.html) 向该项目添加了一个可执行文件，它告诉 CMake 用指定的源文件生成一个可执行文件，第一个参数是可执行文件的名字，第二个参数是要编译生成这个可执行文件所依赖的源文件。