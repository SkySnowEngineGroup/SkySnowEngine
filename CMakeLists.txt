#
# Copyright (c) 2020-2022 the PhoneixEngine project.
# Open source is written by liuqian(SkySnow)、zhangshuangxue(Calence)
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
#======
# cmake文件，编译各个平台对应的IDE工程
# 其中vs和xcode的工程文件是可以动态调试源码
# android工程的是打包为aar或者so包，然后android中自己配置cmake链接源码进行动态调试
#======
#指定cmake版本
cmake_minimum_required(VERSION 3.10)
#工程名字
project(SkySnow3D)

#camke 准则
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.12")
	cmake_policy(SET CMP0074 NEW)
endif()
#测试cmake命令行
if(WIN32)
	message("WIN32 Platform 测试数据")
endif()
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 11)

set(DEST_INCLUDE_DIR include/SkySnow3D)

include_directories("${PROJECT_SOURCE_DIR}/SkySnow3D")
file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${DEST_INCLUDE_DIR}/ThirdParty)

add_subdirectory(SkySnow3D)
