cmake_minimum_required(VERSION 3.0)  #允许不小于cmake的版本
project(main)   #工程名字 

#配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

#配置头文件搜索路径
#include_directories()

#配置库文件搜索路径
#link_directories()

#设置需要编译的源文件列表
set(SRC_LIST ./muduo_server.cpp)

#设置可执行文件最终储存的位置
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
#                          PROJECT_SOURCE_DIR 工程的根目录
#PROJECT_SOURCE_DIR 是一个默认的变量，这个变量是和根目录下的 CMakeLists.txt 相同目录
#或者说是与包含了设置项目名称 project() 的 CMakeLists.txt 目录是相同的


# 把.指定路径下的所有源文件名字放入变量名SRC_LIST里面
#aux_source_directory(. SRC_LIST)

#add_executable(server muduo_server.cpp)   #生成可执行文件 通过工程.cpp文件
add_executable(server ${SRC_LIST})#表示生成可执行文件server，由SRC_LIST变量所定义的源文件编译而来

#链接库文件 表示server这个目标程序 需要链接muduo_net muduo_base pthread 这三个库文件
target_link_libraries(server muduo_net muduo_base pthread) 

