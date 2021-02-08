cmake_minimum_required(VERSION 3.16)

#设置项目名称

project(HyperRectanglesRTree)

set(CMAKE_CXX_STANDARD 17)

set(BOOST_ROOT "/usr/local/include/boost")

#添加头文件搜索路径

include_directories(/usr/local/include)

#添加库文件搜索路径

link_directories(/usr/local/lib)

#[[#用于将当前目录下的所有源文件的名字保存在变量 DIR_SRCS 中

aux_source_directory(. DIR_SRCS)]]

add_executable(HyperRectanglesRTree main.cpp interface.cpp)
