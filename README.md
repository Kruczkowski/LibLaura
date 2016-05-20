
LibLaura - a library for binaural sound source localization
===============================================================================

---------------
- Description -
---------------

The library was designed for binaural sound analysis. It is dedicated for
developing audio systems based on two microphones. LibLaura is written in 
C++ language, is easily extensible and it supports binaural sound analysis 
in realtime. It was developed using *CMake build system* under Linux but 
should compile on other operating systems. 


------------
- Features -
------------

    * Single sound source binaural localization.
    * *Cross-corelation* and *GCC-PHAT* time delay estimators are supported.
    * New time delay estimators can be added easily to the library core.
    * *ITD* (Interaural Time Difference) and *ILD* (Interaural Level Difference)
      features calculation.
    * User-defined callback in the processing chain.
    * Easy to use, a few examples of usage are included.
    * Sound sources are supported using audio file (via **libsndfile**) or audio
      device in realtime (via **RtAudio**).


-----------
- Website -
-----------

  http://quefrency.org/liblaura


----------------
- Requirements -
----------------

    * **FFTW**          - http://www.fftw.org
    * **RtAudio**       - http://www.music.mcgill.ca/~gary/rtaudio/
    * **libsndfile**    - http://www.mega-nerd.com/libsndfile/
    * **Doxygen**       - http://www.stack.nl/~dimitri/doxygen/

    *GUI example*:

    * **Qt framework**  - https://www.qt.io/qt-framework/


----------------
- Installation -
----------------

LibLaura uses **CMake** ( http://cmake.org ) system to build the library and
examples. The following steps have to be performed to compile the source code:

1. tar xvf liblaura-0.1.0.tar.gz
2. cd liblaura-0.1.0/
3. cmake .
4. make

The shared and static libraries will be put in "${LIBLAURA_ROOT}/lib"
directory, and binaries of examples will be put in "${LIBLAURA_ROOT}/examples"
and "${LIBLAURA_ROOT}/examples/GUI" directories.

The Doxygen documentation will be available in "${LIBLAURA_ROOT}/doc/html"
folder after calling the 'make doc' command.


--------------------
- Acknowledgements -
--------------------

The **LauraGUI** uses *QT Framework* by The Qt Company ( https://www.qt.io/ )
and the *QCustomPlot* widget by Emanuel Eichhammer ( http://qcustomplot.com ).


