#######  阿巴阿巴 #####
# 添加直接运行脚本文件


#!/bin/bash

set -x

rm -rf `pwd`/build/*
cd `pwd`/build &&
	cmake .. &&
	make
