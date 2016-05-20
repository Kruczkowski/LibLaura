/*
 * LibLaura - a library for binaural sound source localization
 *
 * Copyright (C) 20XX Your name
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

#ifndef DUMMY_H
#define DUMMY_H

#include "lauraestimator.h"

class Dummy : public LauraEstimator{

protected:
     virtual void init(){

 		 // put your code here

		 this->TAG = "DUMMY";
     }

public:
     virtual void process(DATA_Array rightChannel, DATA_Array leftChannel,
                         LauraComplex* rightSpectrum, LauraComplex* leftSpectrum,
                         DATA_Array &result){

		// put your code here
    }

    virtual void close(){

		// put your code here
    }
};

#endif // DUMMY_H


