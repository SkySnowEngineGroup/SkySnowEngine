#
# Copyright (c) 2020-2022 the SkySnowEngine project.
# Open source is written by wangcan(crygl),liuqian(SkySnow),zhangshuangxue(Calence)
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
set(project_name Nuwa)

set(SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

# 遍历读取文件夹名字以及文件名字
# 源码文件遍历
file(GLOB_RECURSE NuwaSource "${SOURCES_DIR}/../Nuwa/*.*")
#message("${NuwaSource}")

foreach(source IN LISTS NuwaSource)
	file(RELATIVE_PATH source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${source}")
	get_filename_component(source_path "${source_rel}" PATH)
	string(REPLACE "/" "\\" source_path_dir "${source_path}")
	source_group("${source_path_dir}" FILES "${source}")
endforeach()

add_library(${project_name} ${NuwaSource})

# 迭代遍历文件夹，然后设置这些文件夹名字给头文件包裹，就省去了手动写
# Nuwa库的一些头文件遍历链接导入
file(GLOB_RECURSE NuwaHeader "${SOURCES_DIR}/../Nuwa/*.h")
#message("Header:${NuwaHeader}")
foreach (SourceHeader IN LISTS NuwaHeader)
	file(RELATIVE_PATH source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${SourceHeader}")
	get_filename_component(source_path "${source_rel}" PATH)
	string(REPLACE "/" "\\" source_path_dir "${source_path}")
	#message("Header Path: ${source_path_dir}")
	target_include_directories(${project_name} PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/${source_path_dir})
endforeach()

# 导入三方依赖库的头文件依赖
target_include_directories(${project_name} PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../ThirdParty/Glad/
						   ${project_name} PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../ThirdParty/glfw3/include/)
#在win32平台使用Pthreads库
if(WIN32)
target_include_directories(${project_name} PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../ThirdParty/pthread_win/pthreads.2/)
endif(WIN32)