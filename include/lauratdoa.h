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

#ifndef LAURATDOA_H
#define LAURATDOA_H

#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <iterator>
#include <algorithm>
#include <math.h>

#include "lauratypes.h"
#include "laurafftw.h"

#include "crosscorr.h"          /* default estimator */

class LauraTDOA{

protected:

    LauraFFT *fft;

    int FRAME_SIZE;             /* size of stream frame */
    int FFT_SIZE;               /* size of fast Fourier transform */
    int BUFF_SIZE;              /* the nearest power of 2 */
    int SAMPLING_RATE;          /* sampling frequency */
    unsigned short CHANNELS;    /* number of channels */
    float VELOCITY;             /* speed of sound */
    float DISTANCE;             /* distance between sensors (microphones) */

    DATA_Array TDOAvalues;
    DATA_Array ITDvalues;
    LauraEstimator* estimator;

    void initializeTDOA(
            float distance  /* distance between microphones */,
            float velocity  /* speed of sound */);
public:

    LauraTDOA(int samplingRate,int frameSize, unsigned short channels, float distance, float velocity);
    ~LauraTDOA();

    /* algorithms */
    void SpectrumCalculation(
            /* input parameters */
            DATA_Array rightChannel,
            DATA_Array leftChannel,
            /* output parameters */
            LauraComplex* &rightSpectrum,
            LauraComplex* &leftSpectrum);
    void DelayEstimation(
            /* input parameters */
            DATA_Array rightChannel,
            DATA_Array leftChannel,
            LauraComplex* rightSpectrum,
            LauraComplex* leftSpectrum,
            /* output parameters */
            DATA_Array &result);
    void TDOA(
            /* input parameters */
            DATA_Array gccPhatResult,
            /* output parameters */
            DATA& TDOA_result,
            DATA& ITD_result);

    /* WINDOWS */
    static DATA hammingWindow(int iterator, int size);
    static DATA bartlettWindow(int iterator, int size);
    static DATA blackmanWindow(int iterator, int size);

    void setEstimator(LauraEstimator* estimator);

    void setSamplingFrequency(unsigned int samplingFreq);
    void setFrameSize(float frameSize);
    void setChannels(unsigned short channels);
    void setDistance(float distance);
    void setVelocity(float velocity);

};

#endif  // LAURATDOA_H

