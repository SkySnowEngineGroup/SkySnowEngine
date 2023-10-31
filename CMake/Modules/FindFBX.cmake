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
if(WIN32)
	set(FBX_DIR "${TPPath}/fbxsdk/windows/2020.3.4")
	target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${FBX_DIR}>/include/)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(fbxPath "${FBX_DIR}/lib/vs2019/x64/debug")
	elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
		set(fbxPath "${FBX_DIR}/lib/vs2019/x64/release")
	endif()
	#message("fbxPath build:${fbxPath}")
	find_library(FBX_LIBRARY
				NAMES libfbxsdk.lib   # 库文件的名称，可根据版本和配置不同
			 	HINTS "${fbxPath}"    # 指定库文件的搜索路径
			)
    find_file(FBX_DLL
              NAMES libfbxsdk.dll
              HINTS "${fbxPath}"      # 适应构建配置
             )
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        file(COPY "${FBX_DLL}" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Debug")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        file(COPY "${FBX_DLL}" DESTINATION "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Release")
    endif()
elseif(APPLE)
	set(FBX_DIR "${TPPath}/fbxsdk/macos/2020.3.4")
	target_include_directories(${PROJECT_NAME} PUBLIC $<BUILD_INTERFACE:${FBX_DIR}>/include/)
	if(CMAKE_BUILD_TYPE STREQUAL "Debug")
		set(fbxPath "${FBX_DIR}/lib/clang/debug")
	elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
		set(fbxPath "${FBX_DIR}/lib/clang/release")
	endif()
	find_library(FBX_LIBRARY
				NAMES libfbxsdk.dylib   # 库文件的名称，可能根据版本和配置不同
			 	HINTS "${fbxPath}"		# 指定库文件的搜索路径
			)
endif(WIN32)


