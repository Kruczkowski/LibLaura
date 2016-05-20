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

#ifndef LAURAESTIMATOR_H
#define LAURAESTIMATOR_H

#include "lauratypes.h"

class LauraEstimator{

protected:
    unsigned int FRAME_SIZE;
    std::string TAG;

    /**
     * @brief User has to override this method. It's called int LauraEstimator::initialize().
     */
    virtual void init()=0;

public:
    void initialize(int buffSize);
    virtual void process(DATA_Array rightChannel, DATA_Array leftChannel,
                         LauraComplex* rightSpectrum, LauraComplex* leftSpectrum,
                         DATA_Array &result)=0;
    void process(DATA_Array stream, 
				 LauraComplex* rightSpectrum, LauraComplex* leftSpectrum, DATA_Array &result);
    virtual void close()=0;
};

#endif // LAURAESTIMATOR_H

