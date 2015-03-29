cmake_minimum_required(VERSION 2.8.7)
project(Scratch)

if(NOT WIN32)
	SET(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

add_library(Scratch
	src/Assert.cpp
	src/CContainer.cpp src/CContainer.h
	src/CDictionary.cpp src/CDictionary.h
	src/CFileStream.cpp src/CFileStream.h
	src/CMemoryStream.cpp src/CMemoryStream.h
	src/CNetworkStream.cpp src/CNetworkStream.h
	src/CStackArray.cpp src/CStackArray.h
	src/CStream.cpp src/CStream.h
	src/CString.cpp src/CString.h
	src/CVectors.cpp src/CVectors.h
	src/Common.cpp src/Common.h
	src/Scratch.h)

if(APPLE)
	set_target_properties(Scratch PROPERTIES MACOSX_RPATH 1)
endif()

set_target_properties(Scratch PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set_target_properties(Scratch PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

if(WIN32)
	add_definitions("/wd4996")
endif()
