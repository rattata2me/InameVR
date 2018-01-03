
cmake_minimum_required(VERSION 2.8)

project(InameVRdiykit)

# project version
set(VERSION_MAJOR 1)
set(VERSION_MINOR 0)
set(VERSION_PATCH 0)

# System architecture
if(NOT PLATFORM)
  if(CMAKE_SIZEOF_VOID_P MATCHES 8)
    set(PLATFORM 64)
  else()
    set(PLATFORM 32)
  endif()
endif()

message(STATUS "Compiling for ${PLATFORM}x architecture")

# System name
if(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_definitions(-DLINUX -DPOSIX)
    set(ARCH_TARGET linux64)
    if(${PLATFORM} MATCHES 32)
    endif()
endif()
if(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    add_definitions(-DOSX -DPOSIX)
    set(ARCH_TARGET osx32)
endif()
if(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    add_definitions(-D_WIN32)
    set(ARCH_TARGET win${PLATFORM})
endif()

#Set include files
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/../include)

#Set source directory
set(PROJECT_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(PROJECT_HEADER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)


set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

set(OUTPUT_NAME diy_driver)

file(GLOB SOURCES "${PROJECT_SOURCE_DIR}/*.cpp"
	"${PROJECT_HEADER_DIR}/*.h"
)


include_directories(
	.
	${HEADER_FILES}
	${PROJECT_HEADER_DIR}
)

find_library(INAMEVR_LIB
	NAMES
		iname_vr
	PATHS
		${CMAKE_CURRENT_SOURCE_DIR}/lib/ 
		${CMAKE_CURRENT_SOURCE_DIR}/../build/ #Delete this, this is just for testing
	PATH_SUFFIXES
    		osx32
    		linux64
    		${WINDOWS_PATH_SUFFIXES}
	NO_DEFAULT_PATH
	NO_CMAKE_FIND_ROOT_PATH
)

find_package( OpenCV REQUIRED )

add_executable(${OUTPUT_NAME} ${SOURCES})

target_link_libraries(${OUTPUT_NAME}
  ${INAMEVR_LIB}
  ${CMAKE_DL_LIBS}
  ${OpenCV_LIBS}
)



