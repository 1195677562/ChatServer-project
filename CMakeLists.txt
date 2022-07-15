cmake_minimum_required(VERSION 3.0)
project(group-chat)

#配置编译选项
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 配置最终的可执行文件输出的路径
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
 
# 配置头文件的搜索路径
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/include/server)
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)   # 查询 json.hpp 头文件 
include_directories(${PROJECT_SOURCE_DIR}/include/server/db) #查询 db 数据库  
include_directories(${PROJECT_SOURCE_DIR}/include/server/model) # 查询 model文件
include_directories(${PROJECT_SOURCE_DIR}/include/server/redis) # 查询 redis.hpp

# 加载子目录
add_subdirectory(src)
