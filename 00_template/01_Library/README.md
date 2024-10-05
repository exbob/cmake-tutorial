# Library

这是一个生成动态链接库的模板。库函数的作用是计算输入数字的平方根，源码的文件结构：

- 动态库的源码放在 src 目录下
- 动态库的头文件源码放在 include 目录下
- 动态库的测试程序源码放在 test 目录下
- 顶层的 CMakeLists.txt 文件中可以设置库的版本号和文件依赖
- 动态库的编程示例源码放在 example 目录下，需要单独编译

编译生成动态库：

```
> cmake -S . -B build
> cmake --build build/
```

生成的动态库和可执行文件都输出到了 `${PROJECT_BINARY_DIR}/output` 目录下：

```
> ls -l build/output/
total 36
lrwxrwxrwx 1 lsc lsc    12 Oct  5 20:22 libmath.so -> libmath.so.0
lrwxrwxrwx 1 lsc lsc    16 Oct  5 20:22 libmath.so.0 -> libmath.so.0.1.4
-rwxr-xr-x 1 lsc lsc 15736 Oct  5 20:22 libmath.so.0.1.4
-rwxr-xr-x 1 lsc lsc 16864 Oct  5 20:22 test
```

test 下的 CMakeLists.txt 有测试功能，执行测试：

```
> cd build/test/
> ctest
Test project /home/lsc/workspace/cmake-tutorial/00_template/01_Library/build/test
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

Total Test time (real) =   0.00 sec
```

测试完成后执行安装：

```
> sudo cmake --install build
-- Install configuration: ""
-- Installing: /usr/local/lib/libmath.so.0.1.4
-- Installing: /usr/local/lib/libmath.so.0
-- Installing: /usr/local/lib/libmath.so
-- Installing: /usr/local/include/libmath.h
```

因为 `${CMAKE_INSTALL_PREFIX}` 的默认值是 `/usr/local` ，所以，库文件会安装到 `/usr/local/lib` 路径下，公共头文件会安装到 `/usr/local/include` 路径下。也可以用 `--prefix` 选项修改 `${CMAKE_INSTALL_PREFIX}` 的值，例如：

```
> cmake --install build --prefix ./build/install
> ls -l build/install/*
build/install/include:
total 4
-rw-r--r-- 1 lsc lsc 324 Oct  5 13:50 libmath.h

build/install/lib:
total 16
lrwxrwxrwx 1 lsc lsc    12 Oct  5 20:31 libmath.so -> libmath.so.0
lrwxrwxrwx 1 lsc lsc    16 Oct  5 20:31 libmath.so.0 -> libmath.so.0.1.4
-rw-r--r-- 1 lsc lsc 15736 Oct  5 20:22 libmath.so.0.1.4
```

安装后要执行一次 `ldconfig -v` ：

```
> sudo ldconfig -v 
```

这个的作用是更新链接器的动态链接库缓存，这样编译应用程序时才能找到刚安装的 libmath 。然后可以编译 example 下的例程：

```
> cd example
> cmake -S . -B build
> cmake --build build
```

可以看到生成的 demo 程序可以链接到 libmath.so.0 ，并且执行成功：

```
> ldd build/demo
        linux-vdso.so.1 (0x00007ffd8d3dc000)
        libmath.so.0 => /usr/local/lib/libmath.so.0 (0x00007f184dfba000)
        libc.so.6 => /lib/x86_64-linux-gnu/libc.so.6 (0x00007f184ddc8000)
        /lib64/ld-linux-x86-64.so.2 (0x00007f184dfd4000)
> ./build/demo
The square root of 4.000000 is 2.000000 .
```