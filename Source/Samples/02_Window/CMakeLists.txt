#
# Copyright (c) 2020-2022 the NuwaEngine project.
# Open source is written by liuqian(SkySnow),zhangshuangxue(Calence),wangcan(crygl)
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

set(SAMPLE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

file(GLOB Sources_lists "${SAMPLE_DIR}/*.cpp")

add_executable(Window ${Sources_lists})

target_include_directories(Window PUBLIC $<BUILD_INTERFACE:${SAMPLE_DIR}/>)

target_link_libraries(Window Nuwa Plugins glfw glad ${OpenGL_LIBRARY}) #ThirdParty