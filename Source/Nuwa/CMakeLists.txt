#
# Copyright (c) 2020-2022 the NuwaEngine project.
# Open source is written by wangcan(crygl)、liuqian(SkySnow)、zhangshuangxue(Calence)
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
set(SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCES_THREADS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Threads/")
set(SOURCE_APPLICATION_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Application/")
set(SOURCE_RS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/RenderSystems/")
set(SOURCE_GRI_DIR "${SOURCE_RS_DIR}/GRI/")
set(SOURCE_GLGRI_DIR "${SOURCE_RS_DIR}/GLGRI/")
set(SOURCE_UTIL_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Utilities/")

file(GLOB Sources_lists "${SOURCES_DIR}/*.cpp"
	                    "${SOURCES_DIR}/*.h"
						"${SOURCES_THREADS_DIR}/*.cpp"
						"${SOURCES_THREADS_DIR}/*.h"
						"${SOURCES_THREADS_DIR}/Posix/*.cpp"
						"${SOURCES_THREADS_DIR}/Posix/*.h"
						"${SOURCE_APPLICATION_DIR}/*.cpp"
						"${SOURCE_APPLICATION_DIR}/*.h"
						"${SOURCE_UTIL_DIR}/*.cpp"
						"${SOURCE_UTIL_DIR}/*.h"
						"${SOURCE_UTIL_DIR}/Log/*.cpp"
						"${SOURCE_UTIL_DIR}/Log/*.h"
						"${SOURCE_RS_DIR}/*.h"
						"${SOURCE_RS_DIR}/*.cpp"
						"${SOURCE_GRI_DIR}/*.h"
						"${SOURCE_GRI_DIR}/*.cpp"
                        "${SOURCE_GLGRI_DIR}/*.h"
						"${SOURCE_GLGRI_DIR}/*.cpp"
						"${SOURCE_GLGRI_DIR}/GLImport/*.h"
						"${SOURCE_GLGRI_DIR}/GLImport*.cpp"
						"${SOURCE_GLGRI_DIR}/Android/*.h"
						"${SOURCE_GLGRI_DIR}/Android/*.cpp"
						"${SOURCE_GLGRI_DIR}/Ios/*.h"
						"${SOURCE_GLGRI_DIR}/Ios/*.cpp"
						"${SOURCE_GLGRI_DIR}/Mac/*.h"
						"${SOURCE_GLGRI_DIR}/Mac/*.cpp"
						"${SOURCE_GLGRI_DIR}/Window/*.h"
						"${SOURCE_GLGRI_DIR}/Window/*.cpp")

foreach(source IN LISTS Sources_lists)
	file(RELATIVE_PATH source_rel "${CMAKE_CURRENT_SOURCE_DIR}" "${source}")
	get_filename_component(source_path "${source_rel}" PATH)
	string(REPLACE "/" "\\" source_path_dir "${source_path}")
	source_group("${source_path_dir}" FILES "${source}")
endforeach()

add_library(Nuwa ${Sources_lists})

target_include_directories(Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCE_APPLICATION_DIR}>/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCES_THREADS_DIR}>/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCES_THREADS_DIR}>/Posix/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCE_UTIL_DIR}>/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCE_UTIL_DIR}>/Log/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCE_RS_DIR}>/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCE_GRI_DIR}>/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCE_GLGRI_DIR}>/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCE_GLGRI_DIR}>/Android/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCE_GLGRI_DIR}>/Ios/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCE_GLGRI_DIR}>/Mac/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCE_GLGRI_DIR}>/Window/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCE_GLGRI_DIR}>/GLImport/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../ThirdParty/Glad/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../ThirdParty/glfw3/include/)
#在win32平台使用Pthreads库
if(WIN32)
target_include_directories(Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../ThirdParty/pthreads_win32/pthreads.2/)
endif(WIN32)