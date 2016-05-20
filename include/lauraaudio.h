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

#ifndef LAURAAUDIO_CLASS_H
#define LAURAAUDIO_CLASS_H

#include <RtAudio.h>
#include <sndfile.hh>
#include <string>

#include "audiocallback.h"
#include "callbackresult.h"
#include "lauratypes.h"

// Platform-dependent sleep routines.
#if defined( __WINDOWS_ASIO__ ) || defined( __WINDOWS_DS__ ) || defined( __WINDOWS_WASAPI__ )
  #include <windows.h>
  #define SLEEP( milliseconds ) Sleep( (DWORD) milliseconds ) 
#else // Unix variants
  #include <unistd.h>
  #define SLEEP( milliseconds ) usleep( (unsigned long) (milliseconds * 1000.0) )
#endif

class LauraAudio
{
    /**
     * @brief The structure of the data passed to processing stage of a stream (input device).
     */
    struct InputData {
        unsigned long bufferBytes;
        unsigned short channels;    // Number of channels
        AudioCallback* callback;    // Pointer to AudioCallback
        bool* mutex;                // Pointer to blockade
        int bufferSize;
    };

	/**
     * @brief The structure of the data passed to processing stage of samples received from a file.
     */
    struct OutputData {
        SndfileHandle *fd;          // Pointer to file
        AudioCallback* callback;    // Pointer to AudioCallback
        bool* mutex;                // Pointer to blockade
        int bufferSize;
    };

private:

	AudioCallback* callback;    /* Callback object */

    /* Fields with informations about audio device and file */
    unsigned int FRAME_SIZE;
	unsigned int SAMPLING_FREQ;
    short CHANNELS;

    /* Field with information about state of stream */
    bool isStopped;
    bool stopIt;

    /* Field blocked access to buffer of stream */
    bool mutex;

    /* PRIVATE METHODS - protorypes */
    RtAudioFormat getRtAudioFormat(int bits_per_sample);
    RtAudioFormat sfToRtFormat(int SFFORMAT);
    void printFileInfo(SndfileHandle sndfile);
    void printDeviceInfo();

public:

    LauraAudio(unsigned int samplingFreq, unsigned int frameSize, unsigned short channels);
    ~LauraAudio();

    /* OPERATIONS ON STREAM - prototypes */
    static int input( void * /*outputBuffer*/, void * inputBuffer, unsigned int nBufferFrames,
            double /*streamTime*/, RtAudioStreamStatus /*status*/, void * data );
    static int output( void *outputBuffer, void * /*inputBuffer*/, unsigned int nBufferFrames,
             double /*streamTime*/, RtAudioStreamStatus /*status*/, void *data );

    /* CONTROL OF OPERATIONS ON STREAM - prototypes */
    int capture(unsigned int device);
    int play(std::string filename, unsigned int device);
    void stop();

    /* GETTERS - prototypes */
    std::string* getDeviceList();
    unsigned int getDeviceCount();
    bool isStreamRunning();
    bool itsStopped();

    /* SETTERS - prototypes */
    void setCallback(AudioCallback* callback);

    /* BLOCKADE INTERFACE - prototypes */
    void lock();
    void unlock();
    bool isLocked();

    void setSamplingFrequency(unsigned int samplingFreq);
    void setFrameSize(float frameSize);
    void setChannels(unsigned short channels);
};

#endif  // LAURAAUDIO_CLASS_H

