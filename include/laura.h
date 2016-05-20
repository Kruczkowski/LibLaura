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

#ifndef LAURA_H
#define LAURA_H

#include "laurabackend.h"
#include "lauraaudio.h"
#include "lauracallback.h"
#include "laurathread.h"
#include "lauratypes.h"
#include "lauralogger.h"

class Laura
{
private:

    LauraBackend* backend;          /* Backend object */
    LauraThread* lauraThread;       /* Thread object */

    unsigned int flags;             /* Flags field */
    unsigned int SAMPLING_RATE;     /* Sampling frequency */

public:

    LauraAudio* audio;              /* Audio object */

    Laura(unsigned int samplingFreq, float frameLength, unsigned short channels,
          float distance, float velocity, unsigned int flags);
    ~Laura();

    void setCallback(LauraCallback* callback, bool initialize);

    void capture(int device,int interval);
    void play(std::string filename, int device,int interval);
    void stop();
    bool isStreamRunning();

    void setEstimator(LauraEstimator* estimator);
    void setSamplingFrequency(unsigned int samplingFreq);
    void setFrameLength(float frameLength);
    void setChannels(unsigned short channels);
    void setDistance(float distance);
    void setVelocity(float velocity);
    void setFlags(unsigned int flags);

    void setLogDir(std::string logDir, unsigned int flag);
    void setLogName(LauraFlag flag, std::string logName);
    void showMessages(unsigned int flag);
    int getSizeOfBuffer();
};

#endif // LAURA_H

