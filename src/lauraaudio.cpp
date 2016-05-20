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

#include <iostream>
#include <string>
#include <string.h>
#include <cstdio>
#include <cstdlib>
#include <iterator>
#include <algorithm>

#include <RtAudio.h>
#include "lauramessenger.h"
#include "lauraaudio.h"

/**
 * @brief LauraAudio::LauraAudio
 * @param samplingFreq
 *          Sampling frequency.
 * @param frameSize
 *          Size of one stream frame.
 * @param channels
 *          Number of channels.
 */
LauraAudio::LauraAudio(unsigned int samplingFreq, unsigned int frameSize, unsigned short channels)
    : SAMPLING_FREQ(samplingFreq),
      FRAME_SIZE(frameSize),
      CHANNELS(channels),
      isStopped(false),
      stopIt(true){
    // Print information on all available devices.
    this->printDeviceInfo();

    // Lock access to stream buffer
    lock();
}
LauraAudio::~LauraAudio(){
}

/* --- OPERATIONS ON STREAM ---*/
/**
 * @brief Operation on data captured from input device.
 * @param inputBuffer
 *          Input data captured from input device.
 * @param nBufferFrames
 *          Size of buffer.
 * @param data
 *          User arguments.
 * @return
 */
int LauraAudio::input( void * /*outputBuffer*/, void * inputBuffer, unsigned int nBufferFrames,
                  double /*streamTime*/, RtAudioStreamStatus /*status*/, void * data ) {

    InputData *iData = (InputData*) data;

    // Initialize buffer
    DATA_Array buff = new DATA[nBufferFrames*iData->channels];

    // Casting data - outputBuffer is streamType array, buff is DATA array
    for(int i=0; i<nBufferFrames * iData->channels; i++) {
        buff[i] = (DATA)((StreamType*)inputBuffer)[i];
    }

    // Unlock access to stream buffer
    *(iData->mutex) = true;

    // Call callback
    iData->callback->setStream(buff);
    delete [] buff;

    return 0;
}

/**
 * @brief LauraAudio::output
 * @param outputBuffer
 *          Output data 
 * @param nBufferFrames
 *          Size of buffer.
 * @param data
 *          User arguments.
 * @return
 */
int LauraAudio::output( void *outputBuffer, void * /*inputBuffer*/, unsigned int nBufferFrames,
                   double /*streamTime*/, RtAudioStreamStatus /*status*/, void *data ) {
    OutputData *oData = (OutputData*) data;
    short channels = oData->fd->channels();

    // Reading data from file, and write to buffer
    sf_count_t count = oData->fd->readf((StreamType*)outputBuffer, nBufferFrames);

    // Initialize buffer
    DATA_Array buff=new DATA[nBufferFrames*channels];

    // Casting data - outputBuffer is streamType array, buff is DATA array
    for(int i=0; i<count*channels; i++) {
        buff[i] = (DATA)((StreamType*)outputBuffer)[i];
    }

    // Handle the last frame
    if ( count < nBufferFrames ){
        for(int i=count; i<nBufferFrames*channels; i++) {
            buff[i] = 0;
        }
    }

    // Unlock access to stream buffer
    *(oData->mutex) = true;

    // Call callback
    oData->callback->setStream(buff);

    delete [] buff;

    // Handle the last frame
    if ( count < nBufferFrames ) {
        unsigned int bytes = nBufferFrames - count  ;
        unsigned int startByte = count;
        memset( (char *)(outputBuffer)+startByte, 0, bytes );
        return 1;
    }
    return 0;
}

/* --- CONTROL OF OPERATIONS ON STREAM --- */
/**
 * @brief LauraAudio::capture
 * @param device
 *          Number of audio device.
 * @return
 */
int LauraAudio::capture(unsigned int device) {
    this->isStopped = false;
    this->stopIt = false;

    RtAudio rtaudio;
    // If counter of devices is 0, no audio device is connected
    if ( rtaudio.getDeviceCount() < 1 ) {
        std::string message ="No audio devices found!";
        throw message;
    }

    // Check properties of the device 
    RtAudio::DeviceInfo deviceInfo = rtaudio.getDeviceInfo(device);
    if(deviceInfo.inputChannels < CHANNELS) {
        std::string message = "Device supports too few channels.";
        throw message;
    }

    // Check sampling rates supported by device
    std::vector<unsigned int>::iterator it;
    it = std::find (deviceInfo.sampleRates.begin(), deviceInfo.sampleRates.end(), SAMPLING_FREQ);
    if (it != deviceInfo.sampleRates.end()){
        std::stringstream message;
        message << "Sample rate " << *it << " is supported by device.";
        LauraMessenger::printInfo(message.str());
    }
    else {
        std::string message = "Sample rate is not supported by the device.";
        throw message;
    }
    // Let RtAudio print messages to stderr.
    rtaudio.showWarnings( true );

    // Set parameters of our stream for input only.
    RtAudio::StreamParameters iParams;
    iParams.deviceId = device;
    iParams.nChannels = CHANNELS;
    iParams.firstChannel = 0;
    RtAudioFormat format = getRtAudioFormat(deviceInfo.nativeFormats);
    InputData data;
    data.channels = CHANNELS;
    data.callback = this->callback;
    data.mutex = &this->mutex;
    try {
        rtaudio.openStream( NULL, &iParams, format, SAMPLING_FREQ, &FRAME_SIZE, &LauraAudio::input, (void *)&data );
        rtaudio.startStream();
    }
    catch ( RtAudioError& e ) {
        if ( rtaudio.isStreamOpen() ) rtaudio.closeStream();
        this->isStopped = true;
        throw e.getMessage();
    }
    LauraMessenger::printInfo("\nCapture...");
    while ( 1 ) {
        SLEEP( 100 ); // wake every 100 ms to check if we're done
        if ( !rtaudio.isStreamRunning() ) break;
        else if( this->stopIt ) break;
    }
cleanup:
    if ( rtaudio.isStreamOpen() ) rtaudio.closeStream();
    this->isStopped = true;
    stop();
    return 0;
}

/**
 * @brief LauraAudio::play
 * @param file
 *          File name to play
 * @param device
 *          Number of audio device.
 * @return
 */
int LauraAudio::play(std::string filepath, unsigned int device) {
    this->isStopped = false;
    this->stopIt = false;
    RtAudio rtaudio;
    if ( rtaudio.getDeviceCount() < 1 ) {
        std::string message = "No audio devices found!";
        throw message;
    }
    OutputData data;
    SndfileHandle file = SndfileHandle(filepath.c_str());
    if(!file){
        std::string message = "Unable to find or open file!\nIt is possible that the path is too long.";
        throw message;
    }
    printFileInfo(file);
    data.fd = &file;

    // To get device's info, and to check if device support appropriate amount channels
    RtAudio::DeviceInfo deviceInfo = rtaudio.getDeviceInfo(device);
    if(deviceInfo.inputChannels < CHANNELS) {
        std::string message = "Device support to few channels.";
        throw message;
    }

    // Set parameters of our stream for output only.
    RtAudio::StreamParameters oParams;
    oParams.deviceId = device;
    oParams.nChannels = file.channels();
    oParams.firstChannel = 0;
    data.mutex = &this->mutex;
    data.callback = this->callback;
    RtAudioFormat format = sfToRtFormat(file.format());
    try {
        rtaudio.openStream( &oParams, NULL, format, file.samplerate(), &FRAME_SIZE, &LauraAudio::output, (void *)&data );
        rtaudio.startStream();
    }
    catch ( RtAudioError& e ) {
        rtaudio.closeStream();
        this->isStopped = true;
        throw e.getMessage();
    }
    LauraMessenger::printInfo("Playing...");
    while ( 1 ) {
        SLEEP( 100 ); // wake every 100 ms to check if the stream is still running
        if ( !rtaudio.isStreamRunning() ) break;
        else if( this->stopIt ) break;
    }
cleanup:
    rtaudio.closeStream();
    this->isStopped = true;
    stop();
    return 0;
}

/**
 * @brief Closing audio stream.
 */
void LauraAudio::stop() {
    if(!this->stopIt){
        this->stopIt = true;
        LauraMessenger::printInfo("Stopped.");
        lock();
    }
}

/* --- GETTERS --- */
/**
 * @brief LauraAudio::getDeviceList
 * @return String array with names of devices.
 */
std::string* LauraAudio::getDeviceList() {
    RtAudio rtaudio;
    std::string* devicesNames;
    int deviceCount = rtaudio.getDeviceCount();
    if( deviceCount < 0 ) {
        devicesNames = new std::string[1];
        devicesNames[0] = "null";
        return devicesNames;
    }
    devicesNames = new std::string[deviceCount];
    for(int count = 0; count<deviceCount ; count++) {
        devicesNames[count] = rtaudio.getDeviceInfo(count).name;
    }
    return devicesNames;
}
/**
 * @brief LauraAudio::getDeviceCount
 * @return The number of devices.
 */
unsigned int LauraAudio::getDeviceCount() {
    RtAudio rtaudio;
    int deviceCount = rtaudio.getDeviceCount();
    if( deviceCount <= 0 ) {
        return 0;
    }
    return deviceCount;
}

/* --- SETTERS --- */
/**
 * @brief LauraAudio::setCallback
 * @param Sets callback object
 */
void LauraAudio::setCallback(AudioCallback* callback) {
    this->callback = callback;
}

/* --- PRIVATE METHODS --- */
/**
 * @brief Returns audio format as RtAudioFormat
 * @param bits_per_sample
 *      Bits per sample
 * @return
 *      Audio format as RtAudioFormat
 */
RtAudioFormat LauraAudio::getRtAudioFormat(int bits_per_sample){
    RtAudioFormat format;
    switch(bits_per_sample){
        case 8:
            format = RTAUDIO_SINT8;
            break;
        case 16:
            format = RTAUDIO_SINT16;
            break;
        case 24:
            format = RTAUDIO_SINT24;
            break;
        case 32:
            format = RTAUDIO_SINT32;
            break;
        default:
            format = RTAUDIO_FLOAT64;
            break;
    }
    return format;
}
/**
 * @brief Returns audio format as RtAudio
 * @param SFFORMAT
 *      Audio format as declared in libsndfile
 * @return
 *      Audio format as RtAudioFormat
 */
RtAudioFormat LauraAudio::sfToRtFormat(int SFFORMAT){
    RtAudioFormat format;
    if(SFFORMAT & SF_FORMAT_PCM_S8)
        format = RTAUDIO_SINT8;
    else if(SFFORMAT & SF_FORMAT_PCM_16)
        format = RTAUDIO_SINT16;
    else if(SFFORMAT & SF_FORMAT_PCM_24)
        format = RTAUDIO_SINT24;
    else if(SFFORMAT & SF_FORMAT_PCM_32)
        format = RTAUDIO_SINT32;
    else if(SFFORMAT & SF_FORMAT_FLOAT)
        format = RTAUDIO_FLOAT32;
    else if(SFFORMAT & SF_FORMAT_DOUBLE)
        format = RTAUDIO_FLOAT64;
    else
        format = RTAUDIO_SINT16;
    return format;
}
/**
 * @brief Prints information on all available devices.
 */
void LauraAudio::printDeviceInfo() {
    RtAudio rtaudio;
    if ( rtaudio.getDeviceCount() >= 1 ){
        std::stringstream message;
        message << "Info about audio devices:\n";
        for(int i=0; i<rtaudio.getDeviceCount(); i++) {
            RtAudio::DeviceInfo info = rtaudio.getDeviceInfo(i);
            message<<i<<".\n";
            message << "probed :" << info.probed << std::endl;
            message << "name :" << info.name << std::endl;
            message << "outputChannels :" << info.outputChannels << std::endl;
            message << "inputChannels :" << info.inputChannels << std::endl;
            message << "duplexChannels :" << info.duplexChannels << std::endl;
            message << "isDefaultOutput :" << info.isDefaultOutput << std::endl;
            message << "isDefaultInput :" << info.isDefaultInput << std::endl;
            message << "sampleRates :";
            std::vector<unsigned int>::iterator it;
            for(it = info.sampleRates.begin(); it< info.sampleRates.end(); it++)
            {
                message<<*it<<", ";
            }
            message << std::endl;
            message << "nativeFormats :" << info.nativeFormats << std::endl <<std::endl;
        }
        LauraMessenger::printInfo(message.str());
    }
}
/**
 * @brief Prints information about audio file
 * @param The sndfile handle
 */
void LauraAudio::printFileInfo(SndfileHandle sndfile) {
    std::stringstream message;
    message << "Audio file info:" << std::endl;
    message << " Sampling rate of the input wave file is "<< sndfile.samplerate() <<" Hz" << std::endl;
    message << " Number of bits per sample is: "<< sfToRtFormat(sndfile.format())/2 <<"bits" << std::endl;
    message << " The number of channels of the file is "<< sndfile.channels() << " channels" << std::endl;

    LauraMessenger::printInfo(message.str());
}
/**
 * @brief LauraAudio::isStreamRunning
 * @return Status of the stream
 */
bool LauraAudio::isStreamRunning(){
    return !(this->isStopped);
}
/**
 * @brief Returns information about the stream
 * @return
 */
bool LauraAudio::itsStopped(){
    return !(this->stopIt);
}

 /* --- BLOCKADE INTERFACE --- */
/**
 * @brief Lock access to stream buffer.
 */
void LauraAudio::lock(){
    mutex = false;
}

/**
 * @brief Unlock access to stream buffer.
 */
void LauraAudio::unlock(){
    mutex = true;
}

/**
 * @brief LauraAudio::isLocked
 * @return Access status
 */
bool LauraAudio::isLocked(){
    return !mutex;
}

/**
 * @brief Sets sampling frequency
 * @param samplingFreq
 */
void LauraAudio::setSamplingFrequency(unsigned int samplingFreq){
    this->SAMPLING_FREQ = samplingFreq;
}

/**
 * @brief Sets the size of audio frame in samples
 * @param frameSize
 */
void LauraAudio::setFrameSize(float frameSize){
this->FRAME_SIZE = frameSize;
}

/**
 * @brief Sets the number of channels
 * @param channels
 */
void LauraAudio::setChannels(unsigned short channels){
    this->CHANNELS = channels;
}

