cmake_minimum_required(VERSION 2.8.7)
project(Scratch)

if(NOT WIN32)
	SET(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

set(presrc "src/Scratch")

if(CMAKE_BUILD_TYPE)
	if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
		add_definitions(-DDEBUG)
	endif()
endif()

add_library(Scratch
	${presrc}/Assert.cpp
	${presrc}/CContainer.cpp ${presrc}/CContainer.h
	${presrc}/CDictionary.cpp ${presrc}/CDictionary.h
	${presrc}/CFileStream.cpp ${presrc}/CFileStream.h
	${presrc}/CMemoryStream.cpp ${presrc}/CMemoryStream.h
	${presrc}/CNetworkStream.cpp ${presrc}/CNetworkStream.h
	${presrc}/CStackArray.cpp ${presrc}/CStackArray.h
	${presrc}/CStream.cpp ${presrc}/CStream.h
	${presrc}/CString.cpp ${presrc}/CString.h
	${presrc}/CFilename.cpp ${presrc}/CFilename.h
	${presrc}/CVectors.cpp ${presrc}/CVectors.h
	${presrc}/CMutex.cpp ${presrc}/CMutex.h
	${presrc}/Common.cpp ${presrc}/Common.h
	${presrc}/Scratch.h)

if(APPLE)
	set_target_properties(Scratch PROPERTIES MACOSX_RPATH 1)
endif()

set_target_properties(Scratch PROPERTIES ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set_target_properties(Scratch PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

if(WIN32)
	add_definitions("/wd4996")
endif()

set(presrc_tests "src/ScratchTests")

add_executable(ScratchTests
	${presrc_tests}/main.cpp)

find_package(Threads)
message("thread libs: ${CMAKE_THREAD_LIBS_INIT}")
target_link_libraries(ScratchTests Scratch ${CMAKE_THREAD_LIBS_INIT})

include_directories(src/Scratch)

enable_testing()
add_test(CString ScratchTests CString)
add_test(CFilename ScratchTests CFilename)
add_test(CStackArray ScratchTests CStackArray)
add_test(CDictionary ScratchTests CDictionary)
add_test(CFileStream ScratchTests CFileStream)
add_test(CMutex ScratchTests CMutex)
