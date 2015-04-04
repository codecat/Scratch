cmake_minimum_required(VERSION 2.8.7)
project(Scratch)

if(NOT WIN32)
	SET(CMAKE_CXX_FLAGS "-std=c++0x")
endif()

set(presrc "src/Scratch")

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

target_link_libraries(ScratchTests Scratch)

include_directories(src/Scratch)
