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

#include "laurathread.h"
#include "lauramessenger.h"

/**
 * @brief Starts thread with operation in backend. It waits for an access to
 * stream buffer.
 * @param param
 *      Data for thread.
 * @return
 */

void* LauraThread::backendWorker(void* param){
    LauraMessenger::printInfo("Backend thread is open.");
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    pthread_testcancel();
    BackendThreadData* data = reinterpret_cast<BackendThreadData*>(param);

    while (true){
        // Wait while access to stream is locked.
        while(data->audio->isLocked()) {
            // Break if audio is stopped.
            if(!data->audio->itsStopped()) {
                break;
            }
        }
        // Users interval
        usleep(1000*data->interval);

        // Break if audio is stopped.
        if(!data->audio->itsStopped()) {
            break;
        }
        // Calculating
        data->backend->Calculate();

        // Lock access to stream.
        data->audio->lock();
    }
    LauraMessenger::printInfo("Backend thread is closed.");
    delete data;
    pthread_exit(NULL);
}

/**
 * @brief Starts audio playback and backend
 * @param param
 *          Data for thread.
 */
void* LauraThread::playbackWorker(void* param){
    LauraMessenger::printInfo("Playback thread is open.");
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    pthread_testcancel();
    AudioThreadData* data = reinterpret_cast<AudioThreadData*>(param);
    try{
        data->audio->play(data->filename, data->device);
    }catch(std::string & e){
        LauraMessenger::printError("LauraThread::playbackWorker "+e);
    }
    *(data->threadIsRunning) = false;
    LauraMessenger::printInfo("Playback thread is closed.");
    delete data;
    pthread_exit(NULL);
}

/**
 * @brief Starts audio capturing and backend
 * @param param
 *          Data for thread.
 */
void* LauraThread::captureWorker(void* param){
    LauraMessenger::printInfo("Capture thread is open.");
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    pthread_testcancel();
    AudioThreadData* data = reinterpret_cast<AudioThreadData*>(param);
    try{
        data->audio->capture(data->device);
    }catch(std::string & e){
        LauraMessenger::printError("LauraThread::captureWorker "+e);
    }
    *(data->threadIsRunning) = false;
    LauraMessenger::printInfo("Capture thread is closed.");
    delete data;
    pthread_exit(NULL);
}

/**
 * @brief Starts capturing thread
 * @param audio
 *          Reference to audio object.
 * @param device
 *          ID of the device.
 * @param backend
 *          Reference to backend object.
 * @param interval
 *          Interval of time of waiting backend for unlocking stream buffer.
 */
void LauraThread::capture(LauraAudio* &audio, int device,
                                     LauraBackend* &backend,int interval){
    _isRunning = true;
    // Creating data for thread
    AudioThreadData* audioData = new AudioThreadData(audio, device , "", &_isRunning);
    BackendThreadData* backendData = new BackendThreadData(audio,backend,interval);
    // Starting thread
    pthread_create(&this->audioThread, NULL, LauraThread::captureWorker, audioData);
    pthread_detach(audioThread);
    pthread_create(&this->backendThread, NULL, LauraThread::backendWorker, backendData);
    pthread_detach(backendThread);
}

/**
 * @brief Starts playback thread
 * @param audio
 *          Reference to audio object.
 * @param device
 *          ID of the device.
 * @param backend
 *          Reference to backend object.
 * @param interval
 *          Interval of time of waiting backend for unlocking stream buffer.
 */
void LauraThread::playback(LauraAudio* &audio, int device, std::string filename,
                                      LauraBackend* &backend,int interval){
    _isRunning = true;
    // Creating data for thread
    AudioThreadData* audioData = new AudioThreadData(audio, device , filename, &_isRunning);
    BackendThreadData* backendData = new BackendThreadData(audio,backend,interval);

    // Starting thread
    pthread_create(&this->audioThread, NULL, LauraThread::playbackWorker, audioData);
    pthread_detach(audioThread);
    pthread_create(&this->backendThread, NULL, LauraThread::backendWorker, backendData);
    pthread_detach(backendThread);
}

/**
 * @brief Stops audio stream
 * @param audio
 *          Reference to audio object.
 */
void LauraThread::stop(LauraAudio* &audio){
    if(audio->isStreamRunning()){
        audio->stop();
    }
    // Thread is stopped
    _isRunning = false;
}

/**
 * @brief Returns the status of thread
 * @return Status of thread
 */
bool LauraThread::isRunning(){
    return _isRunning;
}

