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

#include <sys/time.h>

#include "laurabackend.h"
#include "lauramessenger.h"

/**
 * @brief LauraBackend::LauraBackend
 * @param samplingFreq
 *          Sampling frequency.
 * @param frameSize
 *          Size of frame.
 * @param channels
 *          Number of channels.
 * @param distance
 *          Distance between microphones (ears).
 * @param velocity
 *          Velocity of sound.
 * @param _flags
 *          Flags indicate the returned fields in callback.
 */
LauraBackend::LauraBackend(unsigned int samplingFreq, unsigned int frameSize, 
                           unsigned short channels, float distance, float velocity, unsigned int _flags)
    : SAMPLING_RATE(samplingFreq),
      FRAME_SIZE(frameSize),
      CHANNELS(channels),
      flags(_flags){

    this->BUFF_SIZE = nextPow2(FRAME_SIZE);
    this->FFT_SIZE = BUFF_SIZE*2-1;

    // Initialization of the LauraTDOA object with a sound source localization algorithms.
    tdoa = new LauraTDOA(SAMPLING_RATE, FRAME_SIZE, CHANNELS, distance, velocity);

    audioCallback = new AudioCallback();
    callbackResult = new CallbackResult();

    stream = new DATA[FRAME_SIZE*CHANNELS];
    delay = new DATA[FFT_SIZE];
    rightSpectrum = (LauraComplex*)(new LauraComplex[FFT_SIZE]);
    leftSpectrum = (LauraComplex*)(new LauraComplex[FFT_SIZE]);
    rightModule = new DATA[BUFF_SIZE];
    leftModule = new DATA[BUFF_SIZE];

    // Data arrays are empty
    notNull = false;
    loggerIsSet = false;
    time = 0.0;
}

LauraBackend::~LauraBackend(){

    // Data arrays are empty
    notNull = false;

    delete [] delay;
    delete [] stream;
    delete [] rightSpectrum;
    delete [] leftSpectrum;
    delete [] rightModule;
    delete [] leftModule;

    delete audioCallback;
}

/**
 * @brief Main method in this class. Performs operations on arrays and performs
 * an analysis of the buffer.
 */
void LauraBackend::Calculate(){
    struct timeval  tv1, tv2;
    stream = audioCallback->getStream(); // Get stream buffer.
    DATA rightInputBuffer[FFT_SIZE],
        leftInputBuffer[FFT_SIZE];

    this->separationChannels(stream, rightInputBuffer, leftInputBuffer);

    time = (audioCallback->getFamreCounter()*FRAME_SIZE*1000.0)/SAMPLING_RATE;
    gettimeofday(&tv1, NULL);

    if(flags & SPECTRUM) // Spectrum calculation
    tdoa->SpectrumCalculation(
                rightInputBuffer,
                leftInputBuffer,
                (LauraComplex*&)rightSpectrum,
                (LauraComplex*&)leftSpectrum);

    // Cross-Correlation Calculation
    if(flags & CORRELATION)
    tdoa->DelayEstimation(
                rightInputBuffer,
                leftInputBuffer,
                rightSpectrum,
                leftSpectrum,
                delay);

    // Calculation TDOA and ITD
    if(flags & TDOA || flags & ITD)
    tdoa->TDOA(
                delay,
                TDOA_result, ITD_result);

	//Print info about time of calculations
    //gettimeofday(&tv2, NULL);
    //std::stringstream timeMessage;
    //timeMessage << "Time calculations: " << tv2.tv_usec - tv1.tv_usec << " us";
    //LauraMessenger::printInfo(timeMessage.str());

    // Arrays are not null
    if(!notNull)
        notNull = true;

    // Set values for user callback result
    setCallbackResult(this->callbackResult);

    // Log data to file
    if(loggerIsSet)
        logger->writeLogToFile(this->callbackResult, time);

    // Call user callback
    userCallback->provider(this->callbackResult);
}

/**
 * @brief Separates chanels of stream
 * @param stream
 *      Input buffer
 * @param rightChannel
 *      Output first buffer
 * @param leftChannel
 *      Output second buffer
 */
void LauraBackend::separationChannels(DATA_Array stream, DATA_Array rightChannel, DATA_Array leftChannel){
    DATA rightLevel = 0,
         leftLevel = 0;

    for(int i=0; i<BUFF_SIZE; i++) {
      
        // Split channels and using the Hamming window
        rightChannel[i] = stream[i*2] * tdoa->hammingWindow(i,FRAME_SIZE);
        leftChannel[i] = stream[i*2+1] * tdoa->hammingWindow(i,FRAME_SIZE);

        rightChannel[i+BUFF_SIZE-1] = 0;
        leftChannel[i+BUFF_SIZE-1] = 0;

        if(flags & ILD){
            rightLevel += stream[i*2];
            leftLevel += stream[i*2+1];
        }
    }

    if(flags & ILD){
        // Interaural Level Differences
        DATA halfInterval = 0;

        if(sizeof(StreamType) > 1/* byte */) halfInterval = pow(256,sizeof(StreamType))/2;

        rightLevel = rightLevel/BUFF_SIZE + halfInterval;
        leftLevel = leftLevel/BUFF_SIZE + halfInterval;

        ILD_result = 20.0 * log10(rightLevel / (leftLevel + 1e-16)) /*dB*/;
    }

}

/**
 * @brief Calculates the module of complex spectrum
 * @return
 */
int LauraBackend::CalculateSpectrumModule() {
    if(notNull) {
        for(int i=0; i<FRAME_SIZE; i++) {
            rightModule[i] =  std::abs(rightSpectrum[i]);
            leftModule[i] =  std::abs(leftSpectrum[i]);
        }
        return 1;
    }else return 0;
}

/**
 * @brief Sets data from fields of this object to callBackResult.
 * @param callBackResult
 *          Result of call of callback.
 */
void LauraBackend::setCallbackResult(CallbackResult* &callBackResult){
    callBackResult->clear();
    callBackResult->setTime(time);
    if(flags & TDOA){
        callBackResult->add(TDOA_result, TDOA);
    }
    if(flags & ITD){
        callBackResult->add(ITD_result, ITD);
    }
    if(flags & ILD){
        callBackResult->add(ILD_result, ILD);
    }
    if(flags & CORRELATION){
        callBackResult->add(delay, CORRELATION);
    }
    if(flags & SPECTRUM){
        this->CalculateSpectrumModule();
        callBackResult->add(rightModule, leftModule, SPECTRUM);
    }
    if(flags & STREAM){
        callBackResult->add(stream, STREAM);
    }

}
/**
 * @brief Sets object of LauraLogger
 * @param logger
 */
void LauraBackend::setLogger(LauraLogger *logger){
    this->logger = logger;
    this->loggerIsSet = true;
}

/**
 * @brief Sets time delay estimator
 * @param estimator
 */

void LauraBackend::setEstimator(LauraEstimator* estimator){
    this->tdoa->setEstimator(estimator);
}

/**
 * @brief Sets sampling frequency
 * @param samplingFreq
 */

void LauraBackend::setSamplingFrequency(unsigned int samplingFreq){
    this->SAMPLING_RATE = samplingFreq;
}

/**
 * @brief Sets the frame size
 * @param frameSize
 */

void LauraBackend::setFrameSize(float frameSize){
    this->FRAME_SIZE = frameSize;
}

/**
 * @brief Sets number of channels
 * @param channels
 */

void LauraBackend::setChannels(unsigned short channels){
    this->CHANNELS = channels;
}

/**
 * @brief Sets the distance between microphones
 * @param distance
 */

void LauraBackend::setDistance(float distance){
    this->tdoa->setDistance(distance);
}

/**
 * @brief Sets the velocity of sound
 * @param velocity
 */

void LauraBackend::setVelocity(float velocity){
    this->tdoa->setVelocity(velocity);
}

/**
 * @brief Sets flags for callback.
 * @param flags
 */

void LauraBackend::setFlags(unsigned int flags){
    this->flags = flags;
}

