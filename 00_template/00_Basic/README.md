# Basic

一个简单模板，适合只有一个源文件的简单程序。

将 main.c 文件编译生成可执行文件 basic，可执行文件的名字可以在 CMakeLists.txt 文件的 `set(program basic)` 命令中修改，可以修改项目名称和版本号。支持生成 Debug 和 Release 两种版本，Debug 版本包含 `-g` 和 `-Wall` 编译选项，可以打印输出调试信息。打印调试信息的函数在 Config.h.in 文件中定义。下面是基本用法：

编译生成一个 Release 版本：

```
> cmake -S . -B Release -DCMAKE_BUILD_TYPE=Release
> cmake --build Release/
> ./Release/basic 
Project Basic, Version 1.0
```

编译生成一个 Debug 版本

```
> cmake -S . -B Debug -DCMAKE_BUILD_TYPE=Debug
> cmake --build Debug/
> ./Debug/basic 
Project Basic, Version 1.0
/home/lsc/workspace/cmake-tutorial/00_template/00_Basic/main.c[0008], main : debug message
```

