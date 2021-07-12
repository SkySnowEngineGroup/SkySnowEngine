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
#

set(SOURCES_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(PLUGINS_DIR "${CMAKE_CURRENT_SOURCE_DIR}/Plugins/")
set(THIRDPARTY_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/ThirdParty/")

#find OpenGL Library
if(WIN32)
    set(OpenGL_LIBRARY opengl32)
elseif(UNIX AND NOT APPLE)
elseif(APPLE)
    include_directories(/System/Library/Frameworks)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(OpenGL_LIBRARY OpenGL)
    find_library(IOKit_LIBRARY IOKit)
    find_library(CoreVideo_LIBRARY CoreVideo)
    message("find library OpenGL Library ${OpenGL_LIBRARY}")
endif(WIN32)

include_directories("${SOURCES_DIR}/Nuwa")
include_directories("${PLUGINS_DIR}/Plugins")
include_directories("${THIRDPARTY_BASE_DIR}/ThirdParty")

add_subdirectory(Nuwa)
add_subdirectory(Plugins)
add_subdirectory(Samples)
add_subdirectory(ThirdParty)