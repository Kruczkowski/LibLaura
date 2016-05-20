set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(LIBS)

# Laura
list(APPEND LIBS laura)

# RtAudio
find_package(RtAudio REQUIRED)
include_directories(${RtAudio_INCLUDE_DIR})
list(APPEND LIBS ${RtAudio_LIBRARY})

# FFTW
find_package(FFTW REQUIRED)
include_directories(${FFTW_INCLUDES})
list(APPEND LIBS ${FFTW_LIBRARIES})

# Threads
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)
list(APPEND LIBS Threads::Threads)

# SndFile
find_library(SNDFILE sndfile)
list(APPEND LIBS ${SNDFILE})

add_executable (localization_from_file localization_from_file.cpp)
add_executable (localization_from_device localization_from_device.cpp)

target_link_libraries (localization_from_file LINK_PUBLIC ${LIBS})
target_link_libraries (localization_from_device LINK_PUBLIC ${LIBS})