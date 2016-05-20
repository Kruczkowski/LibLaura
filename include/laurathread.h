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

#ifndef LAURATHREAD_H
#define LAURATHREAD_H

#include <iostream>

#include "laurabackend.h"
#include "lauraaudio.h"
#include "lauratypes.h"

/**
 * @brief Class responsible for multithreading.
 */
class LauraThread
{

    /**
     * @brief Private structure of the data reported to the threads.
     */
    struct AudioThreadData{
        LauraAudio* audio;      // Pointer to LauraAudio
        int device;             // Audio device number
        std::string filename;   // Path to file, empty if "capture"
        bool* threadIsRunning;  // Pointer to information about thread state

        AudioThreadData(LauraAudio* _audio,int _device,std::string _filename, bool* _threadIsRunning)
            :audio(_audio), device(_device),filename(_filename), threadIsRunning(_threadIsRunning){}
    };
    struct BackendThreadData{
        LauraAudio* audio;      // Pointer to LauraAudio
        LauraBackend* backend;  // Pointer to LauraBackend
        int interval;           // Interval of time for waiting backend for unlocking stream buffer

        BackendThreadData(LauraAudio* _audio,LauraBackend* _backend,int _interval)
            :audio(_audio), backend(_backend),interval(_interval){}
    };

    pthread_t audioThread, backendThread;   // Thread Object

    bool _isRunning;    // State of the thread

public:

    void capture(LauraAudio* &audio, int device,LauraBackend* &backend,int backendInterval);
    void playback(LauraAudio* &audio, int device, std::string filename,LauraBackend* &backend,int backendInterval);
    void stop(LauraAudio* &audio);
    bool isRunning();

    static void* backendWorker(void* param);
    static void* playbackWorker(void* param);
    static void* captureWorker(void* param);
};

#endif // LAURATHREAD_H

