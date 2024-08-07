# Step3_2 目标的属性

本例中，子目录 `libs` 下的 `libmath.c` 定义了 `mysqrt()` 函数，用于计算一个浮点数的平方根，通过动态链接库的方式供其他程序调用，`main.c` 要调用 libmath 的 `mysqrt()` 执行计算，就必须包含头文件 `libs/libmath.h` ，而 `libmath.c` 本身则不需要。这个需求可以用 `target_include_directories()` 命令和 `INTERFACE` 权限来表达。

在 `libs/CMakeLists.txt` 文件中增加一行：

``` CMake
target_include_directories(math INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
```

`${CMAKE_CURRENT_SOURCE_DIR}` 是 cmake 当前正在处理的源码目录的绝对路径，所有链接 libmath 的目标文件都会将其加入头文件搜索路径，而 `libmath.c` 本身则不会。`mani.c` 文件只需写 `#include "libmath.h"`，不用设置 `libmath.h` 的路径。

编译：

``` bash
> cmake -S . -B build
> cd build
> VERBOSE=1 make | grep cc
cd /home/lsc/workspace/cmake-tutorial/05-step3_2/build/libs && /usr/bin/cc -Dmath_EXPORTS  -fPIC   -o CMakeFiles/math.dir/libmath.c.o   -c /home/lsc/workspace/cmake-tutorial/05-step3_2/libs/libmath.c
/usr/bin/cc -fPIC   -shared -Wl,-soname,libmath.so -o libmath.so CMakeFiles/math.dir/libmath.c.o
/usr/bin/cc  -I/home/lsc/workspace/cmake-tutorial/05-step3_2/build -I/home/lsc/workspace/cmake-tutorial/05-step3_2/libs   -o CMakeFiles/step3.dir/main.c.o   -c /home/lsc/workspace/cmake-tutorial/05-step3_2/main.c
/usr/bin/cc   -rdynamic CMakeFiles/step3.dir/main.c.o  -o step3  -Wl,-rpath,/home/lsc/workspace/cmake-tutorial/05-step3_2/build/libs libs/libmath.so
```

可以看到，编译 `main.c` 的时候，添加了 `-I/home/lsc/workspace/cmake-tutorial/05-step3_2/libs` 参数。