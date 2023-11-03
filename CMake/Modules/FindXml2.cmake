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
#Link FbxSDK

set(TPPath "${CMAKE_CURRENT_SOURCE_DIR}/source/ThirdParty")
if(APPLE)
	target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${TPPath}>/libxml2/include/libxml2/libxml)
	find_library(XML2_LIBRARY
				 NAMES libxml2.a   					# 库文件的名称，可根据版本和配置不同
	 			 HINTS "${TPPath}/libxml2/lib"  # 指定库文件的搜索路径
				)
	# message("libxml2 path:${XML2_LIBRARY}")
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		file(COPY "${XML2_LIBRARY}" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug")
	elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
		file(COPY "${XML2_LIBRARY}" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release")
	endif()
endif(APPLE)