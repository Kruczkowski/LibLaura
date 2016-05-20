cmake_minimum_required (VERSION 2.8)
project (LibLaura)

# set(CMAKE_VERBOSE_MAKEFILE ON)

# Loading source files
set(laura_SOURCES src/laura.cpp)
list(APPEND laura_SOURCES
    src/callbackresult.cpp 
    src/lauraaudio.cpp 
    src/laurabackend.cpp 
    src/lauraestimator.cpp
    src/lauratdoa.cpp 
    src/laurathread.cpp
    src/lauralogger.cpp
    src/lauramessenger.cpp)

set(CMAKE_BUILD_TYPE Release)
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

#set(audioOutput "__LINUX_ALSA__")
#set(audioOutput "__LINUX_PULSE__")
set(audioOutput "__UNIX_JACK__")
#set(audioOutput "__UNIX_OSS__")
#set(audioOutput "__MACOSX_CORE__")
#set(audioOutput "__WINDOWS_DS__")
#set(audioOutput "__WINDOWS_ASIO__")
#set(audioOutput "__WINDOWS_WASAPI__")

include_directories("include")
include_directories("modules")
add_definitions("-std=c++11 -fPIC -O3 -msse -msse2 -mfpmath=sse -ftree-vectorize -D${audioOutput}")
  
message(STATUS "Audio input/output: " ${audioOutput})

add_subdirectory(examples)
add_subdirectory(examples/GUI)

# Finding libraries
set(LIBS)

# RtAudio
find_package(RtAudio REQUIRED)
include_directories(${RtAudio_INCLUDE_DIR})
list(APPEND LIBS ${RtAudio_LIBRARY})
if(RtAudio_FOUND)
    message(STATUS "RtAudio found.")
endif(RtAudio_FOUND)

# FFTW
find_package(FFTW REQUIRED)
include_directories(${FFTW_INCLUDES})
list(APPEND LIBS ${FFTW_LIBRARIES})

# SndFile
find_package(SndFile REQUIRED)
include_directories(${SNDFILE_INCLUDE_DIRS})
list(APPEND LIBS ${SNDFILE_LIBRARIES})

# Threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
list(APPEND LIBS Threads::Threads)

# Doxygen
find_package(Doxygen)
if(DOXYGEN_FOUND)
add_custom_target(doc
    ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/doc/doxyfile.cfg
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/doc
)
endif(DOXYGEN_FOUND)

# Clean all target
add_custom_target(clean-all
    COMMAND ${CMAKE_BUILD_TOOL} clean
    COMMAND rm -f ./CMakeCache.txt ./cmake_install.cmake ./Makefile
    COMMAND rm -rf ./CMakeFiles ./lib ./doc/latex ./doc/html
    COMMAND rm -f ./examples/CMakeCache.txt ./examples/cmake_install.cmake ./examples/Makefile
    COMMAND rm -rf ./examples/CMakeFiles
    COMMAND rm -f ./examples/GUI/CMakeCache.txt ./examples/GUI/cmake_install.cmake ./examples/GUI/Makefile
    COMMAND rm -rf ./examples/GUI/CMakeFiles
)

# Building library
add_library(objlib OBJECT ${laura_SOURCES})
set_property(TARGET ${objlib} PROPERTY POSITION_INDEPENDENT_CODE 1)
add_library(laura SHARED $<TARGET_OBJECTS:objlib>)
add_library(laura_static STATIC $<TARGET_OBJECTS:objlib>)

# Output directory
file(MAKE_DIRECTORY lib)

