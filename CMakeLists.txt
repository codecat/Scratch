cmake_minimum_required(VERSION 2.8.9)
project(Scratch)

if(NOT WIN32)
	SET(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

add_library(Scratch SHARED
	Assert.cpp
	CContainer.cpp CContainer.h
	CDictionary.cpp CDictionary.h
	CFileStream.cpp CFileStream.h
	CMemoryStream.cpp CMemoryStream.h
	CNetworkStream.cpp CNetworkStream.h
	CStackArray.cpp CStackArray.h
	CStream.cpp CStream.h
	CString.cpp CString.h
	CVectors.cpp CVectors.h
	Common.cpp Common.h
	Scratch.h)

if(APPLE)
	set_target_properties(Scratch PROPERTIES MACOSX_RPATH 1)
endif()

set_target_properties(Scratch PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set_target_properties(Scratch PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

if(WIN32)
	add_definitions("/wd4996")
endif()
