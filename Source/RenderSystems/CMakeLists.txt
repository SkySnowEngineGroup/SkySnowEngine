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
#GFX Render hardware interface
set(SOURCE_GLRHI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/GFXRHI/GLRHI")
set(SOURCE_GLES3RHI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/GFXRHI/GLES3RHI")
file(GLOB Sources_lists "${SOURCES_DIR}/*.cpp"
                        "${SOURCES_DIR}/*.h"
						"${SOURCES_DIR}/GFXRHI/*.h"
						"${SOURCES_DIR}/GFXRHI/*.cpp"
                        "${SOURCE_GLRHI_DIR}/*.h"
						"${SOURCE_GLES3RHI_DIR}/*.h"
						"${SOURCE_GLRHI_DIR}/*.cpp"
						"${SOURCE_GLES3RHI_DIR}/*.cpp")

add_library(RenderSystems ${Sources_lists})

target_include_directories(RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/
                           RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/GFXRHI/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCE_GLRHI_DIR}>/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCE_GLES3RHI_DIR}>/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../ThirdParty/GLAD/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../ThirdParty/glfw3/include/)
