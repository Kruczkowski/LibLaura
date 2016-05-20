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

#include "callbackresult.h"

CallbackResult::CallbackResult(){
    isDownloaded = false;
    isUploaded = true;
}

/**
 * @brief Initialize empty CallbackResult
 * @param flags
 *          Flags of the returned fields.
 * @param FRAME_SIZE
 *          Size of the frame.
 * @param CHANNELS
 *          Number of channels.
 */

void CallbackResult::initialize(unsigned int flags, int FRAME_SIZE, short CHANNELS){
    int buffSize = nextPow2(FRAME_SIZE);
    this->setTime(0.0);
    if(flags & TDOA){
        this->add(0.0, TDOA);
    }
    if(flags & ITD){
        this->add(0.0, ITD);
    }
    if(flags & ILD){
        this->add(0.0, ILD);
    }
    if(flags & CORRELATION){
        DATA_Array CORR_result = new DATA[buffSize*2-1];
        for(int i=0; i<buffSize*2-1;i++) CORR_result[i] = 0;
        this->add(CORR_result, CORRELATION);
    }
    if(flags & SPECTRUM){
        DATA_Array spectrumModule = new DATA[buffSize*2-1];
        for(int i=0; i<buffSize*2-1;i++) spectrumModule[i] = 0;
        this->add(spectrumModule,spectrumModule, SPECTRUM);
    }
    if(flags & STREAM){
        DATA_Array stream=new DATA[FRAME_SIZE*CHANNELS];
        for(int i=0; i<FRAME_SIZE*CHANNELS;i++) stream[i] = 0;
        this->add(stream, STREAM);
    }
}

/**
 * @brief Clears the contener
 */

void CallbackResult::clear(){
    results.clear();
}
CallbackResult::~CallbackResult(){
    this->clear();
}

/**
 * @brief Sets the time of playback
 * @param time time of playback
 */

void CallbackResult::setTime(double time){
    this->time = time;
}

/**
 * @brief Gets the time of playback
 * @return
 */

double CallbackResult::getTime(){
    return time;
}

/**
 * @brief Adds single value.
 * @param input
 *          Input data as single value.
 * @param type
 *          Type of adding data.
 */

void CallbackResult::add(DATA input, LauraFlag type){
    while(isDownloaded);
    isUploaded = true;
    LauraResultStruct lauraStruct;
    lauraStruct.data.value = input;
    lauraStruct.type = type;

    results.erase(type);
    results[type] = lauraStruct;
    isUploaded = false;
}

/**
 * @brief Adds one-dimensional array.
 * @param input
 *          Input data as one-dimensional array.
 * @param type
 *          Type of adding data.
 */
void CallbackResult::add(DATA_Array input, LauraFlag type){
    while(isDownloaded);
    isUploaded = true;
    LauraResultStruct lauraStruct;
    lauraStruct.data.array= input;
    lauraStruct.type = type;

    if(results.count(type) > 0){
        delete [] results[type].data.array;
    }
    results.erase(type);
    results[type] = lauraStruct;
    isUploaded = false;
}

/**
 * @brief Adds two-dimensional array.
 * @param input
 *          Input data as two-dimensional array.
 * @param type
 *          Type of adding data.
 */

void CallbackResult::add(DATA_Array input_1, DATA_Array input_2, LauraFlag type){
    while(isDownloaded);
    isUploaded = true;
    LauraResultStruct lauraStruct;
    lauraStruct.data.array2D[0] = input_1;
    lauraStruct.data.array2D[1] = input_2;
    lauraStruct.type = type;
    if(results.count(type) > 0){
        delete [] results[type].data.array2D[0];
        delete [] results[type].data.array2D[1];
    }
    results.erase(type);
    results[type] = lauraStruct;
    isUploaded = false;
}

/**
 * @brief Getter of single value data.
 * @param type
 *          Type of getting data.
 * @param output
 *          Reference to the output field.
 * @return Status
 */

int CallbackResult::get(LauraFlag type, DATA &output){
    while(isUploaded);
    isDownloaded = true;
    if(results.count(type) < 1)
        return 0;
    output = results[type].data.value;
    isDownloaded = false;
    return 1;
}

/**
 * @brief Getter of one-dimensional array.
 * @param type
 *          Type of getting data.
 * @param output
 *          Reference to the output field.
 * @return Status
 */

int CallbackResult::get(LauraFlag type, DATA_Array &output){
    while(isUploaded);
    isDownloaded = true;
    if(results.count(type) < 1)
        return 0;
    output = results[type].data.array;
    isDownloaded = false;
    return 1;
}

/**
 * @brief Getter of two one-dimensional array.
 * @param type
 *          Type of getting data.
 * @param output_1
 *          Reference to the first output field.
 * @param output_2
 *          Reference to the second output field.
 * @return Status
 */

int CallbackResult::get(LauraFlag type, DATA_Array &output_1, DATA_Array &output_2){
    while(isUploaded);
    isDownloaded = true;
    if(results.count(type) < 1)
        return 0;
    output_1 = results[type].data.array2D[0];
    output_2 = results[type].data.array2D[1];
    isDownloaded = false;
    return 1;
}

