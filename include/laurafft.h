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

#ifndef LAURAFFT_H
#define LAURAFFT_H

#include "lauratypes.h"

class LauraFFT
{

public:
    virtual void FFT(DATA_Array input, LauraComplex* &output, int FFT_SIZE)=0;
    virtual void iFFT(LauraComplex* input, DATA_Array &output, int iFFT_SIZE)=0;

    void ifftshift(DATA_Array input, DATA_Array &output, int BUFF_SIZE){
        int FFT_SIZE = BUFF_SIZE*2-1;
        for(int i=0;i<BUFF_SIZE;i++) {
            output[ i ] = input[ i + BUFF_SIZE ] / FFT_SIZE;
            if(i<BUFF_SIZE-1)
                output[ i + BUFF_SIZE ] = input[ i ] / FFT_SIZE;
        }
    }
};

#endif // LAURAFFT_H

