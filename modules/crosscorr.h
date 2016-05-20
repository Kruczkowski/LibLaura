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

#ifndef CROSSCORR_H
#define CROSSCORR_H

#include "lauraestimator.h"

class CrossCorr : public LauraEstimator{
     DATA_Array gccPhatResult;
protected:
     virtual void init(){
         this->TAG = "CrossCorrelation";
     }
public:
     virtual void process(DATA_Array rightChannel, DATA_Array leftChannel,
                         LauraComplex* rightSpectrum, LauraComplex* leftSpectrum,
                         DATA_Array &result){

         DATA max = 0;
         for(int tau = 0; tau < FRAME_SIZE-1;tau++)
         {
             result[FRAME_SIZE-tau] = 0;
             result[FRAME_SIZE+tau] = 0;
             for (int t = 0; t < FRAME_SIZE; t++){
                 if(t - tau >= 0){
                     result[FRAME_SIZE-tau] += rightChannel[t-tau] * leftChannel[t];
                     if(tau>0)
                     result[FRAME_SIZE+tau] += leftChannel[t-tau] * rightChannel[t];
                 }
             }

             if(max<result[FRAME_SIZE-tau])
                 max = result[FRAME_SIZE-tau];
             if(max<result[FRAME_SIZE+tau])
                 max = result[FRAME_SIZE+tau];
         }

         for(int i=0;i<FRAME_SIZE;i++){
             result[FRAME_SIZE-i] /= max;
             if(i>0)
                 result[FRAME_SIZE+i] /= max;
         }
    }

    virtual void close(){
    }
};

#endif // CROSSCORR_H

