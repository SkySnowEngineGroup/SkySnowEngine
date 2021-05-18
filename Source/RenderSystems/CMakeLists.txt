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

# Define target name
set (TARGET_NAME RenderSystems)

# dispaly folder in MSVS
#set_property(GLOBAL PROPERTY USE_FOLDERS ON)


set(SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

#GFX Render hardware interface
set(SOURCE_RHI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/RHI")
set(SOURCE_GFXRHI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/GFXRHI")
set(SOURCE_GLRHI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/GFXRHI/GLRHI")
set(SOURCE_GLES3RHI_DIR "${CMAKE_CURRENT_SOURCE_DIR}/GFXRHI/GLES3RHI")


file(GLOB Sources_lists "${SOURCES_DIR}/*.cpp"
                        "${SOURCES_DIR}/*.h"
						"${SOURCE_GFXRHI_DIR}/*.h"
						"${SOURCE_GFXRHI_DIR}/*.cpp"
                        "${SOURCE_GLRHI_DIR}/*.h"
						"${SOURCE_GLES3RHI_DIR}/*.h"
						"${SOURCE_GLRHI_DIR}/*.cpp"
						"${SOURCE_GLES3RHI_DIR}/*.cpp"
						"${SOURCE_RHI_DIR}/*.cpp"
						"${SOURCE_RHI_DIR}/*.h")

#RHI分组
file(GLOB Sources_RHI_lists "${SOURCE_RHI_DIR}/*.cpp"
						"${SOURCE_RHI_DIR}/*.h")
SOURCE_GROUP("Source Files\\RHI" FILES ${Sources_RHI_lists})

#GFXRHI分组
file(GLOB Sources_GFXRHI_lists "${SOURCE_GFXRHI_DIR}/*.cpp"
						"${SOURCE_GFXRHI_DIR}/*.h")
SOURCE_GROUP("Source Files\\GFXRHI" FILES ${Sources_GFXRHI_lists})

#GLRHI分组
file(GLOB Sources_GLRHI_lists "${SOURCE_GLRHI_DIR}/*.cpp"
						"${SOURCE_GLRHI_DIR}/*.h")
SOURCE_GROUP("Source Files\\GFXRHI\\GLRHI" FILES ${Sources_GLRHI_lists})

#GLES3RHI分组
file(GLOB Sources_GLES3RHI_lists "${SOURCE_GLES3RHI_DIR}/*.cpp"
						"${SOURCE_GLES3RHI_DIR}/*.h")
SOURCE_GROUP("Source Files\\GFXRHI\\GLES3RHI" FILES ${Sources_GLES3RHI_lists})

 
add_library(RenderSystems ${Sources_lists})
target_include_directories(RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCE_RHI_DIR}>/
                           RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/GFXRHI/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCE_GLRHI_DIR}>/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCE_GLES3RHI_DIR}>/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../ThirdParty/GLAD/
						   RenderSystems PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../ThirdParty/glfw3/include/)


