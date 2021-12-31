#
# Copyright (c) 2020-2022 the NuwaEngine project.
# Open source is written by liuqian(SkySnow),zhangshuangxue(Calence),wangcan(crygl)
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

set(project_name pthread_win)
set(SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB Sources_lists "${SOURCES_DIR}/pthreads.2/implement.h"
                        "${SOURCES_DIR}/pthreads.2/pthread.h"
                        "${SOURCES_DIR}/pthreads.2/sched.h"
                        "${SOURCES_DIR}/pthreads.2/semaphore.h"
					    "${SOURCES_DIR}/pthreads.2/pthread.c")

include_directories(
	${CMAKE_CURRENT_SOURCE_DIR}/pthreads.2
)

foreach(source IN LISTS Sources_lists)
	file(RELATIVE_PATH source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${source}")
	get_filename_component(source_path "${source_rel}" PATH)
	string(REPLACE "/" "\\" source_path_dir "${source_path}")
	source_group("${source_path_dir}" FILES "${source}")
endforeach()

set(CompilerFlags
	CMAKE_CXX_FLAGS
	CMAKE_CXX_FLAGS_DEBUG
	CMAKE_CXX_FLAGS_RELEASE
	CMAKE_C_FLAGS
	CMAKE_C_FLAGS_DEBUG
	CMAKE_C_FLAGS_RELEASE
	)
foreach(CompilerFlag ${CompilerFlags})
	string(REPLACE "/MD" "/MT" ${CompilerFlag} "${${CompilerFlag}}")
endforeach()

add_library(${project_name} SHARED ${Sources_lists})

set(project_compile_options -DHAVE_CONFIG_H)

target_compile_options(${project_name} PRIVATE ${project_compile_options})

target_link_libraries(${project_name} PRIVATE ${MSVC_LIBS})

target_include_directories(${project_name} PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/
                           ${project_name} PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/pthreads.2/
						  )