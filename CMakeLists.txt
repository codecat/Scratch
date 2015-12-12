cmake_minimum_required(VERSION 2.8.7)
project(Scratch)

if(NOT WIN32)
	SET(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

set(presrc "Scratch")

if(CMAKE_BUILD_TYPE)
	if(${CMAKE_BUILD_TYPE} STREQUAL Debug)
		add_definitions(-DDEBUG)
	endif()
endif()

add_library(Scratch
	${presrc}/Assert.cpp
	${presrc}/CContainer.cpp ${presrc}/CContainer.h
	${presrc}/CDictionary.cpp ${presrc}/CDictionary.h
	${presrc}/CException.cpp ${presrc}/CException.h
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

set(presrc_tests "ScratchTests")

add_executable(ScratchTests
	${presrc_tests}/main.cpp)

if(WIN32)
	target_link_libraries(ScratchTests Scratch)
else()
	find_package(Threads)
	message("thread libs: ${CMAKE_THREAD_LIBS_INIT}")
	target_link_libraries(Scratch ${CMAKE_THREAD_LIBS_INIT})
	include_directories(Scratch)
	target_link_libraries(ScratchTests Scratch stdc++)
endif()

enable_testing()
add_test(String ScratchTests String)
add_test(Filename ScratchTests Filename)
add_test(StackArray ScratchTests StackArray)
add_test(Dictionary ScratchTests Dictionary)
add_test(FileStream ScratchTests FileStream)
add_test(Mutex ScratchTests Mutex)
add_test(Exception ScratchTests Exception)
