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
	${presrc}/Assert.hpp
	${presrc}/Dictionary.hpp
	${presrc}/Exception.hpp
	${presrc}/FileStream.hpp
	${presrc}/MemoryStream.hpp
	${presrc}/NetworkStream.hpp
	${presrc}/StackArray.hpp
	${presrc}/Stream.hpp
	${presrc}/String.hpp
	${presrc}/Function.hpp
	${presrc}/Filename.hpp
	${presrc}/Mutex.hpp
	${presrc}/Common.h
	${presrc}/Scratch.hpp

	${presrc}/utf8.h
)

if(APPLE)
	set_target_properties(Scratch PROPERTIES MACOSX_RPATH 1)
endif()

set_target_properties(Scratch PROPERTIES LINKER_LANGUAGE CXX)

set(presrc_tests "ScratchTests")

add_executable(ScratchTests ${presrc_tests}/main.cpp)
add_executable(ScratchTests_No_ThreadSafe ${presrc_tests}/main_no_threadsafe.cpp)

if(NOT WIN32)
	find_package(Threads)
	target_link_libraries(ScratchTests ${CMAKE_THREAD_LIBS_INIT} stdc++)
	target_link_libraries(ScratchTests_No_ThreadSafe ${CMAKE_THREAD_LIBS_INIT} stdc++)
endif()

include_directories(Scratch)

enable_testing()

add_test(String ScratchTests String)
add_test(String_NTS ScratchTests_No_ThreadSafe String)
add_test(Filename ScratchTests Filename)
add_test(Filename_NTS ScratchTests_No_ThreadSafe Filename)
add_test(StackArray ScratchTests StackArray)
add_test(StackArray_NTS ScratchTests_No_ThreadSafe StackArray)
add_test(Dictionary ScratchTests Dictionary)
add_test(Dictionary_NTS ScratchTests_No_ThreadSafe Dictionary)
add_test(FileStream ScratchTests FileStream)
add_test(FileStream_NTS ScratchTests_No_ThreadSafe FileStream)
add_test(Mutex ScratchTests Mutex)
add_test(Mutex_NTS ScratchTests_No_ThreadSafe Mutex)
add_test(Exception ScratchTests Exception)
add_test(Exception_NTS ScratchTests_No_ThreadSafe Exception)
add_test(Function ScratchTests Function)
add_test(Function_NTS ScratchTests_No_ThreadSafe Function)
