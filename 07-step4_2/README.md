# Step4_2 输出调试信息

对于 Generate 过程中生成的内容，比如生成器表达式，可以用 [file()](https://cmake.org/cmake/help/latest/command/file.html) 命令将相关信息输出到文件，语法：

```
file(GENERATE OUTPUT <output-file> CONTENT <content>)
```

`GENERATE OUTPUT` 选项表示生成一个文件并向文件输出内容，`<output-file>` 就是要生成的文件，`<content>` 是输出的内容。例如：

```
file(GENERATE OUTPUT debug.log CONTENT "$<IF:0, YES, NO>")
```

它会在 CMakeLists.txt 的同层路径下生成一个名为 `debug.log` 的文件，`$<IF:0, YES, NO>` 是一个生成器表达式，`IF` 是关键字，如果后面第一个参数为 `1` 就返回第二个参数，如果为 `0` 就返回第三个参数。执行 cmake 后查看 `debug.log` 文件，可以看到输出的是 `NO` :

```
> cmake -S . -B build
> cat debug.log 
 NO
```
