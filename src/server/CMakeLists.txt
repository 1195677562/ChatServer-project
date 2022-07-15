
# 定义一个SERC_LIST变量，包含了改目录下所有的源文件
aux_source_directory(. SRC_LIST) # 只包含了server下面的.cpp文件    .表示当前目录下
aux_source_directory(./db DB_LIST)
aux_source_directory(./model MODEL_LIST)
aux_source_directory(./redis REDIS_LIST)

# 指定生成可执行文件
add_executable(ChatServer ${SRC_LIST} ${DB_LIST} ${MODEL_LIST} ${REDIS_LIST})

#   指定链接时可执行文件需要以来的库文件  （链接ChatServer所包含的库文件）
target_link_libraries(ChatServer muduo_net muduo_base mysqlclient hiredis pthread)
#                    依赖的库  muduo_net  muduo_base mysqlclient pthread
