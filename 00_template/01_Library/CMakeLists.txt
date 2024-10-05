cmake_minimum_required(VERSION 3.15)

# 设置一些变量
# ----------------------------------------------------

# 定义项目名称，项目名称就是库的名称
# 本例是一个数学函数库，所以名字是 math，生成的共享库文件是 libmath.so
set(LIB_NAME math)

# 设置版本号，分为三段：MAJOR.MINOR.PATCH
set(MAJOR 0)  # 添加或者修改一些API
set(MINOR 1)  # API没有变化，修改了一些功能
set(PATCH 4)  # API没有变化，修复了一些缺陷

# 显示项目信息和版本号
message(STATUS "Message : lib${LIB_NAME} ${MAJOR}.${MINOR}.${PATCH}")

# 设置链接库依赖的源文件
# 源文件都放在 src 目录下，在 lib${LIB_NAME}_src 变量中列出
set(lib${LIB_NAME}_src src/libmath.c)
# 显示库和依赖的源文件
message(STATUS "Message : lib${LIB_NAME} : ${lib${LIB_NAME}_src}")

# 设置公共头文件
# 头文件都放在 include 目录下，调用库函数需要包括的头文件叫做公共头文件，在 lib${LIB_NAME}_inc 变量中列出
set(lib${LIB_NAME}_inc include/libmath.h)

# ----------------------------------------------------

# 新建项目
project(lib${LIB_NAME} VERSION ${MAJOR}.${MINOR}.${PATCH})

# 生成动态库
add_library(${LIB_NAME} SHARED ${lib${LIB_NAME}_src})

# 设置库文件的版本号
set_target_properties(${LIB_NAME} PROPERTIES 
                        VERSION ${PROJECT_VERSION} # 动态库的版本
                        SOVERSION ${PROJECT_VERSION_MAJOR} # API的版本
                        LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/output # 设置库文件的输出路径
                        PUBLIC_HEADER ${lib${LIB_NAME}_inc} # 设置公共头文件
)

# 设置头文件搜索路径
target_include_directories(${LIB_NAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)

# 安装
install(TARGETS ${LIB_NAME} 
        LIBRARY DESTINATION lib   # 库文件安装到 ${CMAKE_INSTALL_PREFIX}/lib
        PUBLIC_HEADER DESTINATION include # 头文件安装到 ${CMAKE_INSTALL_PREFIX}/include
        )

# 添加 example
# 编译 example 下的文件
# add_subdirectory(example)

# 添加 test
# 编译 test 下的文件
add_subdirectory(test)