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

#ifndef LAURABACKEND_H
#define LAURABACKEND_H

#include <math.h>
#include <memory>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <fftw3.h>

#include "lauratdoa.h"
#include "audiocallback.h"
#include "callbackresult.h"
#include "lauratypes.h"
#include "lauralogger.h"


class LauraBackend
{
    /* Results of the analysis */
    LauraComplex *rightSpectrum, *leftSpectrum;
    DATA_Array delay, stream, rightModule, leftModule;
    DATA TDOA_result, ITD_result, ILD_result;

    /* State of arrays */
    bool notNull;
    bool loggerIsSet;

    /* Flags */
    unsigned int flags;

    /* User callback */
    void setCallbackResult(CallbackResult* &callBackResult);
    CallbackResult* callbackResult;


public:

    LauraTDOA *tdoa;        /* Object class with algoritms */

    unsigned int SAMPLING_RATE;
    unsigned int FRAME_SIZE;
    unsigned short CHANNELS;
    unsigned int BUFF_SIZE;
    unsigned int FFT_SIZE;
    double time;

    LauraBackend(unsigned int samplingFreq, unsigned int frameSize, unsigned short channels, 
                 float distans, float velocity, unsigned int flags);
    ~LauraBackend();

    void separationChannels(DATA_Array stream, 
                            DATA_Array rightChannel, DATA_Array leftChannel);

    void Calculate();
    int CalculateSpectrumModule();

    void setLogger(LauraLogger* logger);
    void setEstimator(LauraEstimator* estimator);
    void setSamplingFrequency(unsigned int samplingFreq);
    void setFrameSize(float frameSize);
    void setChannels(unsigned short channels);
    void setDistance(float distans);
    void setVelocity(float velocity);
    void setFlags(unsigned int flags);

    LauraCallback *userCallback;
    AudioCallback *audioCallback;
    LauraLogger *logger;
};

#endif // LAURABACKEND_H

