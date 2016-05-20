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

#include "lauratdoa.h"
#include "lauratypes.h"

/**
 * @brief LauraTDOA::LauraTDOA
 * @param samplingRate
 *          Sampling frequency.
 * @param FRAME_SIZE
 *          Frame size.
 */
LauraTDOA::LauraTDOA(int samplingRate,int frameSize, unsigned short channels, 
                     float distance, float velocity){
    this->SAMPLING_RATE = samplingRate;
    this->FRAME_SIZE = frameSize;
    this->BUFF_SIZE = nextPow2(FRAME_SIZE);
    this->FFT_SIZE = BUFF_SIZE*2-1;
    this->CHANNELS = channels;
    this->DISTANCE = distance;
    this->VELOCITY = velocity;

    this->fft = new LauraFFTW();
    initializeTDOA(distance, velocity);
    estimator = new CrossCorr();
    estimator->initialize(FRAME_SIZE);
}
LauraTDOA::~LauraTDOA(){
    estimator->close();
    delete [] TDOAvalues;
    delete [] ITDvalues;
}

/**
 * @brief Split channels and calulate the spectrum
 * @param inputBuffer
 *          Input data as single array.
 * @param rightSpectrum
 *          Reference to first complex output array.
 * @param leftSpectrum
 *          Reference to second complex output array.
 * @param ILD_result
 *          Reference ILD output field.
 */
void LauraTDOA::initializeTDOA(float distance, float velocity){
    TDOAvalues = new DATA[FFT_SIZE];
    ITDvalues = new DATA[FFT_SIZE];
    DATA tau, _asin;
    for(int i=0; i<FFT_SIZE; i++) {
        tau = (BUFF_SIZE - i) / (DATA)SAMPLING_RATE;
        _asin = ( tau * velocity) / distance;
        TDOAvalues[i] = asin( _asin ) * 180.0 / M_PI;
        if(isnan(TDOAvalues[i]))
            TDOAvalues[i] = 0;
        ITDvalues[i] = tau*1e+6; // microseconds
    }
}

/**
 * @brief Calculate spectrum
 * @param rightChannel
 *      Input buffer of right channel
 * @param leftChannel
 *      Input buffer of left channel
 * @param rightSpectrum
 *      Output buffer of right spectrum
 * @param leftSpectrum
 *      Output buffer of left spectrum
 */
void LauraTDOA::SpectrumCalculation(DATA_Array rightChannel, DATA_Array leftChannel, 
                                    LauraComplex* &rightSpectrum, LauraComplex* &leftSpectrum){
    fft->FFT(rightChannel, rightSpectrum, FFT_SIZE);
    fft->FFT(leftChannel, leftSpectrum, FFT_SIZE);
}

/**
 * @brief Calls method in LauraEstimator
 * @param rightChannel
 *          Input array with right stream channel.
 * @param leftChannel
 *          Input array with left stream channel.
 * @param rightSpectrum
 *          Input complex array with right channel spectrum.
 * @param leftSpectrum
 *          Input complex array with left channel spectrum.
 * @param result
 *          Reference to output array.
 */
void LauraTDOA::DelayEstimation(DATA_Array rightChannel, DATA_Array leftChannel, 
                                LauraComplex* rightSpectrum, LauraComplex* leftSpectrum, DATA_Array &result) {
    estimator->process(rightChannel,leftChannel, rightSpectrum, leftSpectrum, result);
}

/**
 * @brief Calculates TDOA
 * @param delay
 *          DelayEstimation result array
 * @param TDOA_result
 *      Reference to field of TDOA result
 * @param ITD_result
 *      Reference to field of ITD result
 */
void LauraTDOA::TDOA(DATA_Array delay, DATA& TDOA_result, DATA& ITD_result) {
    DATA maxDelay = 0;
    int indexOfMaxVariable = 0;

    // Searches the maximum value from delay
    for(int i=0; i<FFT_SIZE; i++) {
        if(maxDelay<delay[i]) {
            maxDelay = delay[i];
            indexOfMaxVariable = i;
        }
    }
    TDOA_result = TDOAvalues[indexOfMaxVariable];
    ITD_result = ITDvalues[indexOfMaxVariable];
}

/**
 * @brief Hamming Window
 * @param iterator
 *      Index of sample
 * @param size
 *      Number of samples
 * @return Value for current sample.
 */
DATA LauraTDOA::hammingWindow(int iterator, int size) {
    return 0.54-0.46*cos(2.0*M_PI*iterator/size);
}

/**
 * @brief Bartlett Window
 * @param iterator
 *      Index of sample
 * @param size
 *      Number of samples
 * @return Value for current sample.
 */
DATA LauraTDOA::bartlettWindow(int iterator, int size) {
    return (1.0-( (2.0*abs( iterator-(size/2.0)))/size ));
}

/**
 * @brief Blackman Window
 * @param iterator
 *      Index of sample
 * @param size
 *      Number of samples
 * @return Value for current sample.
 */
DATA LauraTDOA::blackmanWindow(int iterator, int size) {
    return 0.42-0.5*cos(2.0*M_PI*iterator/size)+0.08*cos(4.0*M_PI*iterator/size);
}

void LauraTDOA::setEstimator(LauraEstimator* estimator){
    this->estimator->close();
    delete this->estimator;

    this->estimator = estimator;
    this->estimator->initialize(FRAME_SIZE);
}

void LauraTDOA::setSamplingFrequency(unsigned int samplingFreq){
    this->SAMPLING_RATE = samplingFreq;
}

void LauraTDOA::setFrameSize(float frameSize){
    this->FRAME_SIZE = frameSize;
    this->BUFF_SIZE = nextPow2(FRAME_SIZE);
    this->FFT_SIZE = BUFF_SIZE*2-1;
}

void LauraTDOA::setChannels(unsigned short channels){
    this->CHANNELS = channels;
}

void LauraTDOA::setDistance(float distance){
    this->DISTANCE = distance;
}

void LauraTDOA::setVelocity(float velocity){
    this->VELOCITY = velocity;
}

