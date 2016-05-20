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

#include "lauramessenger.h"
#include "laura.h"

/**
 * @brief Laura::Laura
 * @param samplingFreq
 *          Sampling frequency.
 * @param frameLength
 *          Length of frame in ms.
 * @param channels
 *          Number of channels.
 * @param distance
 *          Distance between sensors (microphones, ears, etc.).
 * @param velocity
 *          Speed of sound.
 * @param flags
 *          Flags of returned fields in the callback.
 */

Laura::Laura(unsigned int samplingFreq, float frameLength, unsigned short channels, 
			 float distance, float velocity,  unsigned int _flags)
    : flags(_flags) {

    this->SAMPLING_RATE = samplingFreq;
    int frameSize = frameLength * SAMPLING_RATE / 1000.0;

    // Initialize objects
    backend = new LauraBackend(samplingFreq, frameSize, channels, distance, velocity, flags);
    audio = new LauraAudio(samplingFreq, frameSize, channels);
    lauraThread = new LauraThread();

    // Setting the AudioCallback
    audio->setCallback(backend->audioCallback);
}

Laura::~Laura(){
    delete backend;
    delete audio;
    delete lauraThread;
}

/**
 * @brief Sets the callback.
 * @param callback
 *          Reference to LauraCallback overrided by the user.
 * @param initialize
 *          Flag indicates the initialization of CallbackResult.
 */
void Laura::setCallback(LauraCallback* callback, bool initialize){
    if(initialize){
        CallbackResult* initCallbackResult = new CallbackResult();
        initCallbackResult->initialize(this->flags, backend->FRAME_SIZE, backend->CHANNELS);
        callback->provider(initCallbackResult);
    }
    backend->userCallback = callback;
}

/**
 * @brief Running thread for handling all operations in background with reading the data from file.
 * @param filename
 *          Path to file for playback.
 * @param device
 *          ID of audio device.
 *  @param interval
 *          Time interval in ms.
 */
void Laura::play(std::string filename, int device, int interval){
    lauraThread->playback(audio, device, filename, backend, interval);
    usleep(100);
}

/**
 * @brief Running thread for handling all operations in background with capturing data from device input.
 * @param device
 *          ID of audio device.
 *  @param interval
 *          Time interval in ms.
 */
void Laura::capture(int device, int interval){
    lauraThread->capture(audio, device, backend, interval);
    usleep(100);
}

/**
 * @brief Stops operations in the background.
 */
void Laura::stop(){
    lauraThread->stop(audio);
}

/**
 * @brief Returns information about the status of thread.
 */
bool Laura::isStreamRunning(){
    return lauraThread->isRunning();
}

/**
 * @brief Sets time delay estimator
 * @param estimator
 */
void Laura::setEstimator(LauraEstimator* estimator){
	this->backend->setEstimator(estimator);
}

/**
 * @brief Sets sampling frequency
 * @param samplingFreq
 */
void Laura::setSamplingFrequency(unsigned int samplingFreq){
    this->SAMPLING_RATE = samplingFreq;
    this->backend->setSamplingFrequency(samplingFreq);
    this->audio->setSamplingFrequency(samplingFreq);
}

/**
 * @brief Sets the length of audio frame
 * @param frameLength
 */
void Laura::setFrameLength(float frameLength){
    int frameSize = frameLength * SAMPLING_RATE / 1000.0;
    this->backend->setFrameSize(frameSize);
    this->audio->setFrameSize(frameSize);
}

/**
 * @brief Sets the number of channels (not used yet)
 * @param channels
 */
void Laura::setChannels(unsigned short channels){
    this->backend->setChannels(channels);
    this->audio->setChannels(channels);
}

/**
 * @brief Sets the distance between microphones
 * @param distance
 */
void Laura::setDistance(float distance){
    this->backend->setDistance(distance);
}

/**
 * @brief Sets the velocity of sound
 * @param velocity
 */
void Laura::setVelocity(float velocity){
    this->backend->setVelocity(velocity);
}

/**
 * @brief Sets the flags of the returned fields in callback.
 * @param flags
 */
void Laura::setFlags(unsigned int flags){
    this->backend->setFlags(flags);
}

/**
 * @brief Sets the path to save the logs
 * @param logDir
 *          path
 * @param logflag
 *          type of saved results
 */
void Laura::setLogDir(std::string logDir, unsigned int logflag){
    /* NOT B OR (A AND B) */
    if((~logflag | (logflag & flags) ) != ~0){
        LauraMessenger::printError("Laura::setLogDir: LauraLogger can't return result, who aren't declared in Lauras constructor.");
        return;
    }
    backend->setLogger(new LauraLogger(logDir, logflag, backend->FRAME_SIZE, backend->SAMPLING_RATE));
}

/**
 * @brief Sets the log file name
 * @param flag
 *          Type of log
 * @param logName
 *          New file name
 */
void Laura::setLogName(LauraFlag flag, std::string logName){

}

/**
 * @brief Sets the type of printed information
 * @param flag
 *          Type of information
 */
void Laura::showMessages(unsigned int flag){
    LauraMessenger::resetFlags(flag);
}

/**
 * @brief Returns the next power of 2 of size of audio frame
 * @return
 */
int Laura::getSizeOfBuffer(){
    return nextPow2(backend->FRAME_SIZE);
}

