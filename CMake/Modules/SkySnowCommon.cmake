#
# Copyright (c) 2020-2022 the SkySnowEngine project.
# Open source is written by liuqian(SkySnow)、zhangshuangxue(Calence)
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

#add_compile_options(-x objective-c++)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -std=c99")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D__STDC_FORMAT_MACROS")

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
    find_library(CoreMedia_LIBRARY CoreMedia)
    find_library(Iconv_LIBRARY iconv)
    # message("find library COCOA LIBRARY ${COCOA_LIBRARY}")
    # message("find library OpenGL Library ${OpenGL_LIBRARY}")
    # message("find library IOKit LIBRARY ${IOKit_LIBRARY}")
    # message("find library CoreVideo LIBRARY ${CoreVideo_LIBRARY}")
    # message("find library CoreMedia LIBRARY ${CoreMedia_LIBRARY}")
    # message("find library Iconv LIBRARY ${Iconv_LIBRARY}")
endif(WIN32)

