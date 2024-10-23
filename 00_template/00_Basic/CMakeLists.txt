# 规定项目所需的最低 cmake 版本为 3.15
cmake_minimum_required(VERSION 3.15)

# 可以在这里修改项目名称和版本号
project(Basic VERSION 1.0)

# 获得编译的 UTC 时间，存储在 BUILD_TIME 变量
string(TIMESTAMP BUILD_TIME "%Y.%m.%d %H:%M" UTC)
message(STATUS "Build Time: " ${BUILD_TIME})

# 如果存在 git ，就执行获取 git 提交版本
find_package(Git)
if(Git_FOUND)
    message(STATUS "Git found: ${GIT_EXECUTABLE}")
    # 获取最新的 git commit hash，存储在 GIT_HASH 变量
    execute_process(
        COMMAND ${GIT_EXECUTABLE} log -1 --format=%H
        WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR}
        OUTPUT_VARIABLE GIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    
    # 获取最新的 commit 日期，YYYY-MM-DD，存储在 GIT_DATA 变量
    execute_process(COMMAND ${GIT_EXECUTABLE} log -1 --format=%cd --date=default
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE  GIT_DATE
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    message(STATUS "Git Commit ${GIT_HASH}, Date ${GIT_DATE}")
endif()

# 用 main.c 编译生成可执行文件 basic，可以修改可执行文件的名称
set(program basic)
add_executable(${program} main.c)

# 设置配置文件
configure_file(Config.h.in Config.h)
# 将 cmake 的顶层构建目录添加到 include 搜索路径
target_include_directories(${program} PUBLIC "${PROJECT_BINARY_DIR}")

# 如果是 Debug 版本，就添加 __DEBUG__ 宏定义，添加 -Wall 编译选项
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    message(STATUS "Add Debug")
    target_compile_definitions(${program} PRIVATE "__DEBUG__")
    target_compile_options(${program} PRIVATE -Wall)
endif()