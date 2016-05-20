set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
set(LIBS)

# Global CMake options
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

# Configure Qt
find_package(Qt5Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(Qt5Gui REQUIRED)

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

#Qt
list(APPEND LIBS Qt5::Widgets)
list(APPEND LIBS Qt5::PrintSupport)

# Loading source files
file(GLOB_RECURSE UI_FILES src/*.ui)
file(GLOB_RECURSE CODE_FILES src/plot/*.cpp)
file(GLOB_RECURSE CODE_FILES src/*.cpp)
qt5_wrap_ui(UI_HEADERS ${UI_FILES})

# Building executable file
add_executable(LauraGUI
  ${UI_HEADERS}
  ${CODE_FILES}
)
target_link_libraries(LauraGUI LINK_PUBLIC ${LIBS})

