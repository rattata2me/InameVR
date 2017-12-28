
cmake_minimum_required(VERSION 2.8)

project(InameVR)

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
set(HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include)

#Set source directory
set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build/${ARCH_TARGET})

set(CMAKE_CXX_FLAGS         "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG   "${CMAKE_CXX_FLAGS_DEBUG} -Wall -Wextra -pedantic -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O2")

set(OUTPUT_NAME iname_vr)

file(GLOB SOURCES "${SOURCE_DIR}/*.cpp")

file(GLOB HEADERS "${HEADER_DIR}/*.h")

include_directories(
	.
	${HEADER_FILES}
)

add_library(${OUTPUT_NAME} SHARED 
	${SOURCES}
	${HEADERS}
)

