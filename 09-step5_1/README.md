# Step5_1 安装

## 执行

依次执行如下三条命令：

```
> cmake -S . -B build
> cmake --build build
> cmake --install build --prefix ./build/install
```

编译生成的文件会安装到 `./build/install` 路径下的相应文件夹下。本程序安装了三个文件：

- libmath.h，这个是头文件，应该安装到 `${CMAKE_INSTALL_PREFIX}/include` 路径下
- libmath.so，这个是库文件，应该安装到 `${CMAKE_INSTALL_PREFIX}/lib` 路径下
- step5，这个可执行文件，应该安装到 `${CMAKE_INSTALL_PREFIX}/bin` 路径下

需要注意，从 3.15 开始，cmake 支持 `--install` 选项，旧版必须用 `make install` 命令进行安装。

## 解析

CMake 提供了 [install()](https://cmake.org/cmake/help/latest/command/install.html) 命令来设置安装规则，用第一个参数区分不同类型的文件，常用的有：

- `install(TARGETS <target>... [...])`，安装目标文件，包括可执行文件，链接库。
- `install({FILES | PROGRAMS} <file>... [...])`，安装文件，例如头文件，配置文件等。
- `install(DIRECTORY <dir>... [...])`，安装目录，如果文件很多，可以将整个目录安装到指定位置。

这些命令有一些通用的选项：

- `DESTINATION <dir>`，指定文件要安装到哪个路径。
- `PERMISSIONS <permission>` ，设置文件安装后的权限属性，有效值是:
    - 文件所有者的权限: `OWNER_READ`, `OWNER_WRITE`, `OWNER_EXECUTE`, 
    - 用户组的权限：`GROUP_READ`, `GROUP_WRITE`, `GROUP_EXECUTE`, 
    - 其他用户的权限：`WORLD_READ`, `WORLD_WRITE`, `WORLD_EXECUTE`, 
    - 文件所属的用户和用户组：`SETUID` 和 `SETGID` 。
- `RENAME <name>` ，对安装的文件进行重命名。

例如，顶层 CMakeLists.txt 设置了 step5 的安装路径：

```
install(TARGETS step5 DESTINATION bin
        PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
                    GROUP_READ
                    WORLD_READ
        )
```

安装后，step5 的权限：

```
> ls -l build/install/bin/
total 20
-rwxr--r-- 1 lsc lsc 16728 Sep  2 19:48 step5
```

安装路径是相对 [CMAKE_INSTALL_PREFIX](https://cmake.org/cmake/help/latest/variable/CMAKE_INSTALL_PREFIX.html) 的，它在在 Linux 系统下的默认值是 `/usr/local` ，在 Windows 系统下的默认值是 `c:/Program Files/${PROJECT_NAME}` ，如果用 `--install` 选项执行安装，这个路径前缀可以用 `--prefix` 的参数覆盖，可以是绝对路径，也可以是相对路径，例如：

```
> cmake --install build --prefix ./build/install
```

如果要默认的 `/usr/local` 路径下，需要 root 权限执行命令。