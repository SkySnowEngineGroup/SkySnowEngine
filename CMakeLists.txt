#
# Copyright (c) 2020-2022 the PhonelxEngine project.
# Open source is written by wagcan、liuqian(SkySnow)、zhangshuangxue(Calence)
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


#camke 准则
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.12")
	cmake_policy(SET CMP0074 NEW)
endif()

#工程名字
project(Phonenix)

set (CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/CMake/Modules)


set(DEST_INCLUDE_DIR include/Source)

file (MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/${DEST_INCLUDE_DIR}/ThirdParty)

add_subdirectory(Source)
