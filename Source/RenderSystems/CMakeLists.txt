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
set (TARGET_NAME RenderSystems)

set(SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(SOURCE_GRI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/GRI")
set(SOURCE_GLGRI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/GLGRI")


file(GLOB Sources_lists "${SOURCES_DIR}/*.cpp"
                        "${SOURCES_DIR}/*.h"
						"${SOURCE_GRI_DIR}/*.h"
						"${SOURCE_GRI_DIR}/*.cpp"
                        "${SOURCE_GLGRI_DIR}/*.h"
						"${SOURCE_GLGRI_DIR}/*.cpp"
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

add_library(RenderSystems ${Sources_lists})
target_include_directories(RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../Nuwa/
                           RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCE_GRI_DIR}>/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCE_GLGRI_DIR}>/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCE_GLGRI_DIR}>/Android/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCE_GLGRI_DIR}>/Ios/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCE_GLGRI_DIR}>/Mac/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCE_GLGRI_DIR}>/Window/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../ThirdParty/GLAD/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../ThirdParty/glfw3/include/)


