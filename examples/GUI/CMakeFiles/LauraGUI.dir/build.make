# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/piotr/Dokumenty/git/liblaura-0.1.0

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/piotr/Dokumenty/git/liblaura-0.1.0

# Include any dependencies generated for this target.
include examples/GUI/CMakeFiles/LauraGUI.dir/depend.make

# Include the progress variables for this target.
include examples/GUI/CMakeFiles/LauraGUI.dir/progress.make

# Include the compile flags for this target's objects.
include examples/GUI/CMakeFiles/LauraGUI.dir/flags.make

examples/GUI/ui_sourceanalyzergui.h: examples/GUI/src/sourceanalyzergui.ui
	$(CMAKE_COMMAND) -E cmake_progress_report /home/piotr/Dokumenty/git/liblaura-0.1.0/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Generating ui_sourceanalyzergui.h"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/lib/i386-linux-gnu/qt5/bin/uic -o /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/ui_sourceanalyzergui.h /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/sourceanalyzergui.ui

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.o: examples/GUI/CMakeFiles/LauraGUI.dir/flags.make
examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.o: examples/GUI/src/plot/circleplot.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/piotr/Dokumenty/git/liblaura-0.1.0/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.o"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.o -c /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/circleplot.cpp

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.i"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/circleplot.cpp > CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.i

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.s"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/circleplot.cpp -o CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.s

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.o.requires:
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.o.requires

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.o.provides: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.o.requires
	$(MAKE) -f examples/GUI/CMakeFiles/LauraGUI.dir/build.make examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.o.provides.build
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.o.provides

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.o.provides.build: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.o

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.o: examples/GUI/CMakeFiles/LauraGUI.dir/flags.make
examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.o: examples/GUI/src/plot/qcustomplot/qcustomplot.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/piotr/Dokumenty/git/liblaura-0.1.0/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.o"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.o -c /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/qcustomplot/qcustomplot.cpp

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.i"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/qcustomplot/qcustomplot.cpp > CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.i

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.s"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/qcustomplot/qcustomplot.cpp -o CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.s

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.o.requires:
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.o.requires

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.o.provides: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.o.requires
	$(MAKE) -f examples/GUI/CMakeFiles/LauraGUI.dir/build.make examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.o.provides.build
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.o.provides

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.o.provides.build: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.o

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.o: examples/GUI/CMakeFiles/LauraGUI.dir/flags.make
examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.o: examples/GUI/src/plot/plot.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/piotr/Dokumenty/git/liblaura-0.1.0/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.o"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.o -c /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/plot.cpp

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.i"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/plot.cpp > CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.i

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.s"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/plot.cpp -o CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.s

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.o.requires:
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.o.requires

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.o.provides: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.o.requires
	$(MAKE) -f examples/GUI/CMakeFiles/LauraGUI.dir/build.make examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.o.provides.build
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.o.provides

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.o.provides.build: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.o

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.o: examples/GUI/CMakeFiles/LauraGUI.dir/flags.make
examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.o: examples/GUI/src/plot/dynamicplot.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/piotr/Dokumenty/git/liblaura-0.1.0/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.o"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.o -c /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/dynamicplot.cpp

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.i"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/dynamicplot.cpp > CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.i

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.s"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/dynamicplot.cpp -o CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.s

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.o.requires:
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.o.requires

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.o.provides: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.o.requires
	$(MAKE) -f examples/GUI/CMakeFiles/LauraGUI.dir/build.make examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.o.provides.build
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.o.provides

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.o.provides.build: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.o

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.o: examples/GUI/CMakeFiles/LauraGUI.dir/flags.make
examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.o: examples/GUI/src/plot/spectrumplot.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/piotr/Dokumenty/git/liblaura-0.1.0/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.o"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.o -c /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/spectrumplot.cpp

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.i"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/spectrumplot.cpp > CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.i

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.s"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/spectrumplot.cpp -o CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.s

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.o.requires:
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.o.requires

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.o.provides: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.o.requires
	$(MAKE) -f examples/GUI/CMakeFiles/LauraGUI.dir/build.make examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.o.provides.build
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.o.provides

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.o.provides.build: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.o

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.o: examples/GUI/CMakeFiles/LauraGUI.dir/flags.make
examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.o: examples/GUI/src/plot/correlationplot.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/piotr/Dokumenty/git/liblaura-0.1.0/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.o"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.o -c /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/correlationplot.cpp

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.i"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/correlationplot.cpp > CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.i

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.s"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/plot/correlationplot.cpp -o CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.s

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.o.requires:
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.o.requires

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.o.provides: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.o.requires
	$(MAKE) -f examples/GUI/CMakeFiles/LauraGUI.dir/build.make examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.o.provides.build
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.o.provides

examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.o.provides.build: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.o

examples/GUI/CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.o: examples/GUI/CMakeFiles/LauraGUI.dir/flags.make
examples/GUI/CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.o: examples/GUI/src/sourceanalyzergui.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/piotr/Dokumenty/git/liblaura-0.1.0/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/GUI/CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.o"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.o -c /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/sourceanalyzergui.cpp

examples/GUI/CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.i"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/sourceanalyzergui.cpp > CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.i

examples/GUI/CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.s"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/sourceanalyzergui.cpp -o CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.s

examples/GUI/CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.o.requires:
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.o.requires

examples/GUI/CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.o.provides: examples/GUI/CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.o.requires
	$(MAKE) -f examples/GUI/CMakeFiles/LauraGUI.dir/build.make examples/GUI/CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.o.provides.build
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.o.provides

examples/GUI/CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.o.provides.build: examples/GUI/CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.o

examples/GUI/CMakeFiles/LauraGUI.dir/src/main.cpp.o: examples/GUI/CMakeFiles/LauraGUI.dir/flags.make
examples/GUI/CMakeFiles/LauraGUI.dir/src/main.cpp.o: examples/GUI/src/main.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/piotr/Dokumenty/git/liblaura-0.1.0/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/GUI/CMakeFiles/LauraGUI.dir/src/main.cpp.o"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LauraGUI.dir/src/main.cpp.o -c /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/main.cpp

examples/GUI/CMakeFiles/LauraGUI.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LauraGUI.dir/src/main.cpp.i"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/main.cpp > CMakeFiles/LauraGUI.dir/src/main.cpp.i

examples/GUI/CMakeFiles/LauraGUI.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LauraGUI.dir/src/main.cpp.s"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/src/main.cpp -o CMakeFiles/LauraGUI.dir/src/main.cpp.s

examples/GUI/CMakeFiles/LauraGUI.dir/src/main.cpp.o.requires:
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/src/main.cpp.o.requires

examples/GUI/CMakeFiles/LauraGUI.dir/src/main.cpp.o.provides: examples/GUI/CMakeFiles/LauraGUI.dir/src/main.cpp.o.requires
	$(MAKE) -f examples/GUI/CMakeFiles/LauraGUI.dir/build.make examples/GUI/CMakeFiles/LauraGUI.dir/src/main.cpp.o.provides.build
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/src/main.cpp.o.provides

examples/GUI/CMakeFiles/LauraGUI.dir/src/main.cpp.o.provides.build: examples/GUI/CMakeFiles/LauraGUI.dir/src/main.cpp.o

examples/GUI/CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.o: examples/GUI/CMakeFiles/LauraGUI.dir/flags.make
examples/GUI/CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.o: examples/GUI/LauraGUI_automoc.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/piotr/Dokumenty/git/liblaura-0.1.0/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object examples/GUI/CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.o"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.o -c /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/LauraGUI_automoc.cpp

examples/GUI/CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.i"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/LauraGUI_automoc.cpp > CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.i

examples/GUI/CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.s"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/LauraGUI_automoc.cpp -o CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.s

examples/GUI/CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.o.requires:
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.o.requires

examples/GUI/CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.o.provides: examples/GUI/CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.o.requires
	$(MAKE) -f examples/GUI/CMakeFiles/LauraGUI.dir/build.make examples/GUI/CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.o.provides.build
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.o.provides

examples/GUI/CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.o.provides.build: examples/GUI/CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.o

# Object files for target LauraGUI
LauraGUI_OBJECTS = \
"CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.o" \
"CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.o" \
"CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.o" \
"CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.o" \
"CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.o" \
"CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.o" \
"CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.o" \
"CMakeFiles/LauraGUI.dir/src/main.cpp.o" \
"CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.o"

# External object files for target LauraGUI
LauraGUI_EXTERNAL_OBJECTS =

examples/GUI/LauraGUI: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.o
examples/GUI/LauraGUI: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.o
examples/GUI/LauraGUI: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.o
examples/GUI/LauraGUI: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.o
examples/GUI/LauraGUI: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.o
examples/GUI/LauraGUI: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.o
examples/GUI/LauraGUI: examples/GUI/CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.o
examples/GUI/LauraGUI: examples/GUI/CMakeFiles/LauraGUI.dir/src/main.cpp.o
examples/GUI/LauraGUI: examples/GUI/CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.o
examples/GUI/LauraGUI: examples/GUI/CMakeFiles/LauraGUI.dir/build.make
examples/GUI/LauraGUI: lib/liblaura.so
examples/GUI/LauraGUI: /usr/local/lib/librtaudio.so
examples/GUI/LauraGUI: /usr/lib/i386-linux-gnu/libfftw3.so
examples/GUI/LauraGUI: /usr/lib/i386-linux-gnu/libfftw3f.so
examples/GUI/LauraGUI: /usr/lib/i386-linux-gnu/libsndfile.so
examples/GUI/LauraGUI: /usr/lib/i386-linux-gnu/libQt5PrintSupport.so.5.2.1
examples/GUI/LauraGUI: /usr/lib/i386-linux-gnu/libQt5Widgets.so.5.2.1
examples/GUI/LauraGUI: /usr/lib/i386-linux-gnu/libQt5Gui.so.5.2.1
examples/GUI/LauraGUI: /usr/lib/i386-linux-gnu/libQt5Core.so.5.2.1
examples/GUI/LauraGUI: examples/GUI/CMakeFiles/LauraGUI.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking CXX executable LauraGUI"
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/LauraGUI.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
examples/GUI/CMakeFiles/LauraGUI.dir/build: examples/GUI/LauraGUI
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/build

examples/GUI/CMakeFiles/LauraGUI.dir/requires: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/circleplot.cpp.o.requires
examples/GUI/CMakeFiles/LauraGUI.dir/requires: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/qcustomplot/qcustomplot.cpp.o.requires
examples/GUI/CMakeFiles/LauraGUI.dir/requires: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/plot.cpp.o.requires
examples/GUI/CMakeFiles/LauraGUI.dir/requires: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/dynamicplot.cpp.o.requires
examples/GUI/CMakeFiles/LauraGUI.dir/requires: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/spectrumplot.cpp.o.requires
examples/GUI/CMakeFiles/LauraGUI.dir/requires: examples/GUI/CMakeFiles/LauraGUI.dir/src/plot/correlationplot.cpp.o.requires
examples/GUI/CMakeFiles/LauraGUI.dir/requires: examples/GUI/CMakeFiles/LauraGUI.dir/src/sourceanalyzergui.cpp.o.requires
examples/GUI/CMakeFiles/LauraGUI.dir/requires: examples/GUI/CMakeFiles/LauraGUI.dir/src/main.cpp.o.requires
examples/GUI/CMakeFiles/LauraGUI.dir/requires: examples/GUI/CMakeFiles/LauraGUI.dir/LauraGUI_automoc.cpp.o.requires
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/requires

examples/GUI/CMakeFiles/LauraGUI.dir/clean:
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI && $(CMAKE_COMMAND) -P CMakeFiles/LauraGUI.dir/cmake_clean.cmake
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/clean

examples/GUI/CMakeFiles/LauraGUI.dir/depend: examples/GUI/ui_sourceanalyzergui.h
	cd /home/piotr/Dokumenty/git/liblaura-0.1.0 && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/piotr/Dokumenty/git/liblaura-0.1.0 /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI /home/piotr/Dokumenty/git/liblaura-0.1.0 /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI /home/piotr/Dokumenty/git/liblaura-0.1.0/examples/GUI/CMakeFiles/LauraGUI.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : examples/GUI/CMakeFiles/LauraGUI.dir/depend

