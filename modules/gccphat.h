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

#ifndef GCCPHAT_H
#define GCCPHAT_H

#include "lauraestimator.h"
#include "laurafftw.h"

class GccPhat : public LauraEstimator{
     LauraFFT *fft = NULL;
     LauraComplex *conjugateAndMultiply = NULL;
     DATA_Array gccPhatResult;
     int FFT_SIZE;
protected:
     virtual void init(){
         this->TAG = "GCC-PHAT";
         FFT_SIZE = FRAME_SIZE*2-1;
         this->fft = new LauraFFTW();
         conjugateAndMultiply = new LauraComplex[FFT_SIZE];
         gccPhatResult = new DATA[FFT_SIZE];
     }
public:
     virtual void process(DATA_Array rightChannel, DATA_Array leftChannel,
                         LauraComplex* rightSpectrum, LauraComplex* leftSpectrum,
                         DATA_Array &result){

        DATA magnitude;

        for(int i=0; i<FFT_SIZE; i++) {

            // X1(f)X2(f)*
            conjugateAndMultiply[i] = rightSpectrum[i] * std::conj(leftSpectrum[i]);

            // |X1(f)X2(f)*|
            magnitude = std::abs(conjugateAndMultiply[i]);

            //  X1(f)X2(f)* / |X1(f)X2(f)*|
            conjugateAndMultiply[i] /= magnitude;
        }
        fft->iFFT(conjugateAndMultiply,gccPhatResult,FFT_SIZE);

        // reordering halves
        fft->ifftshift(gccPhatResult, result, FRAME_SIZE);
    }

    virtual void close(){
         delete [] conjugateAndMultiply;
         delete [] gccPhatResult;
    }
};

#endif // GCCPHAT_H

