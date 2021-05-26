#
# Copyright (c) 2020-2022 the NuwaEngine project.
# Open source is written by liuqian(SkySnow)、zhangshuangxue(Calence)、wangcan(crygl)
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

set(SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB Sources_lists "${SOURCES_DIR}/*.cpp"
                        "${SOURCES_DIR}/*.h"
					    "${SOURCES_DIR}/pthreads.2/*.c"
					    "${SOURCES_DIR}/pthreads.2/*.h")

foreach(source IN LISTS Sources_lists)
	file(RELATIVE_PATH source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${source}")
	get_filename_component(source_path "${source_rel}" PATH)
	string(REPLACE "/" "\\" source_path_dir "${source_path}")
	source_group("${source_path_dir}" FILES "${source}")
endforeach()

add_library(pthread_win32 ${Sources_lists})

target_include_directories(pthread_win32 PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/
                           pthread_win32 PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/pthreads.2/
						  )