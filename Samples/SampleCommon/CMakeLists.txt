#
# Copyright (c) 2020-2022 the NuwaEngine project.
# Open source is written by liuqian(SkySnow),zhangshuangxue(Calence)
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

set(project_name SampleCommon)
set(SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB_RECURSE SampleCommonSource "${SOURCES_DIR}/../SampleCommon/*.*")

foreach(source IN LISTS SampleCommonSource)
	file(RELATIVE_PATH source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${source}")
	get_filename_component(source_path "${source_rel}" PATH)
	string(REPLACE "/" "\\" source_path_dir "${source_path}")
	source_group("${source_path_dir}" FILES "${source}")
endforeach()

add_library(${project_name} ${SampleCommonSource})

file(GLOB_RECURSE SampleCommonHeader "${SOURCES_DIR}/../SampleCommon/*.h")
#����SampleCommon������ͷ�ļ�
foreach (SourceHeader IN LISTS SampleCommonHeader)
	file(RELATIVE_PATH source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${SourceHeader}")
	get_filename_component(source_path "${source_rel}" PATH)
	string(REPLACE "/" "\\" source_path_dir "${source_path}")
	target_include_directories(${project_name} PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/${source_path_dir})
endforeach()

if(WIN32)
    target_link_libraries(${project_name} SkySnow Plugins glfw ${FBX_LIBRARY} pthread_win ${OpenGL_LIBRARY}) #ThirdParty glad
else()
    target_link_libraries(${project_name} SkySnow Plugins glfw ${FBX_LIBRARY} ${OpenGL_LIBRARY}) #ThirdParty glad
endif(WIN32)
