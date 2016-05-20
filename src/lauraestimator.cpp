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

#include "lauraestimator.h"

/**
 * @brief Initialize object of LauraEstimator abstract class 
 * @param buffSize
 */
void LauraEstimator::initialize(int buffSize){
    this->FRAME_SIZE = nextPow2(buffSize);
    this->init();
}

/**
 * @brief Takes stream as one buffer and separates to two buffers (one per channel)
 * @param stream
 *      Input stream
 * @param rightSpectrum
 *      Input right spectrum buffer
 * @param leftSpectrum
 *      Input left spectrum buffer
 * @param result
 *      Output result of estimation
 */
void LauraEstimator::process(DATA_Array stream, LauraComplex* rightSpectrum, LauraComplex* leftSpectrum, DATA_Array &result){
    if(stream == NULL){
        this->process(NULL, NULL, rightSpectrum, leftSpectrum, result);
    }
    else{
        DATA_Array rightBuffer = new DATA[FRAME_SIZE];
        DATA_Array leftBuffer = new DATA[FRAME_SIZE];

        for(int i=0; i<FRAME_SIZE; i++) {
            rightBuffer[i] = stream[i*2];
            leftBuffer[i] = stream[i*2+1];
        }
        this->process(rightBuffer, leftBuffer, rightSpectrum, leftSpectrum, result);
    }
}

