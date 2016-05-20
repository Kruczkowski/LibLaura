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

/* ------------------------------------------------------------------------------ *
 * LauraLogger writes the results of TDOA, ITD and ILD as single value for one 
 * frame in the following format:
 *
 * time value
 * time value
 *
 * Results of GCCPHAT and SPECTRUM are saved as a array of values for one frame
 * in the following format:
 *
 * time: value0 value1 ... lastValue;
 * time: value0 value1 ... lastValue;
 *
 * ------------------------------------------------------------------------------ */

#ifndef LAURALOGGER_H
#define LAURALOGGER_H

#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <string.h>
#include <sndfile.hh>

#include "lauratypes.h"
#include "callbackresult.h"

class LauraLogger
{
protected:
    unsigned int flags;
    std::string pathToDir;
    unsigned int BUFF_SIZE;
    std::string* fileNames;
    bool firstRunning;
    int SAMPLING_RATE;

    /* Results of the analysis */
    std::ofstream
        TDOA_logfile,
        ITD_logfile,
        ILD_logfile,
        CORR_logfile,
        SPECTRUM_RIGHT_logfile,
        SPECTRUM_LEFT_logfile;
    SndfileHandle
        STREAM_wavfile;

    void init();
    void close();

public:
    LauraLogger(std::string pathToDir, unsigned int flag, 
				unsigned int frameSize, unsigned int samplingFreq);
    ~LauraLogger();
    void writeLogToFile(CallbackResult* result, double time);
    void setFileName(LauraFlag flag, std::string fileName);

};

#endif // LAURALOGGER_H

