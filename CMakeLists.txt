#======
# cmake文件，编译各个平台对应的IDE工程
# 其中vs和xcode的工程文件是可以动态调试源码
# android工程的是打包为aar或者so包，然后android中自己配置cmake链接源码进行动态调试
#======
#指定cmake版本
cmake_minimum_required(VERSION 3.10)
#工程名字
project(Phoneix)

#camke 准则
if(CMAKE_VERSION VERSION_GREATER_EQUAL "3.12")
	cmake_policy(SET CMP0074 NEW)
endif()

set(SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Phoneix/Source/")
set(RENDERSYSTEM_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Phoneix/RenderSystems/")
set(PLUGINS "${CMAKE_CURRENT_SOURCE_DIR}/Phoneix/Plugins/")

file(GLOB SRC_LISTS "${SOURCES_DIR}/*.cpp")

add_executable(Phoneix ${SRC_LISTS})