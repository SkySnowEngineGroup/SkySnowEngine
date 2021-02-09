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

file(GLOB Sources_lists "${SOURCES_DIR}/*.cpp"
	                    "${SOURCES_DIR}/*.h"
						"${SOURCES_THREADS_DIR}/*.cpp"
						"${SOURCES_THREADS_DIR}/*.h"
						"${SOURCES_THREADS_DIR}/Possix/*.cpp"
						"${SOURCES_THREADS_DIR}/Possix/*.h")


#add_library(NuwaEngine ${Sources_lists})
add_library(Nuwa ${Sources_lists})


target_include_directories(Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCES_THREADS_DIR}>/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCES_THREADS_DIR}>/Possix/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../RenderSystems/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../RenderSystems/GFXRHI/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../RenderSystems/GFXRHI/GLES3RHI/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../RenderSystems/GFXRHI/GLRHI/
						   Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../RenderSystems/RHI/)
#在win32平台使用Pthreads库
if(WIN32)
target_include_directories(Nuwa PUBLIC $<BUILD_INTERFACE:${SOURCES_DIR}>/../ThirdParty/pthreads_win32/pthreads.2/)
endif(WIN32)