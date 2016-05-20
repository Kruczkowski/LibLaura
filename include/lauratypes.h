/*
 * LibLaura - a library for binaural sound source localization
 *
 * Copyright (C) 2016 Piotr Kruczkowski <pkruczkowsky@gmail.com>
 *                    Tomasz Maka <tmaka@quefrency.org>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef LAURATYPES_H
#define LAURATYPES_H

#include <iostream>
#include <complex>

#include <RtAudio.h>

/**
 * @brief Data types
 */
typedef float DATA;
typedef DATA* DATA_Array;
typedef DATA_Array* DATA_Array2D;

typedef std::complex<DATA> LauraComplex;

/**
 * @brief Configuration states
 */
enum LauraFlag{
    TDOA = 0x01,
    ITD = 0x02,
    ILD = 0x04,
    CORRELATION = 0x08,
    SPECTRUM = 0x10,
    STREAM = 0x20,
};
enum LauraMessage{
    INFO = 0x01,
    WARNING = 0x02,
    ERROR = 0x04,
    ALLMESSAGES = 0x07
};
static int nextPow2(int value){
    int pow = 0x01;
    while(value>pow) pow <<= 1;
    return pow;
}
template<RtAudioFormat format>
struct Audio;

template<>
struct Audio<RTAUDIO_SINT8>{
    typedef char Format;
};
template<>
struct Audio<RTAUDIO_SINT16>{
    typedef short Format;
};
template<>
struct Audio<RTAUDIO_SINT24>{
    typedef S24 Format;
};
template<>
struct Audio<RTAUDIO_SINT32>{
    typedef signed long Format;
};
template<>
struct Audio<RTAUDIO_FLOAT32>{
    typedef float Format;
};
template<>
struct Audio<RTAUDIO_FLOAT64>{
    typedef double Format;
};

typedef Audio<RTAUDIO_SINT16>::Format StreamType;

#endif // LAURATYPES_H

