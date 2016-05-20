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

#ifndef LAURAFFTW_H
#define LAURAFFTW_H

#include <fftw3.h>

#include "laurafft.h"

class LauraFFTW : public LauraFFT
{
public:
    virtual void FFT(DATA_Array input, LauraComplex* &output, int FFT_SIZE){
        if(sizeof(DATA) == 4){
            fftwf_plan plan = fftwf_plan_dft_r2c_1d(FFT_SIZE, 
													(float*)input, 
													reinterpret_cast<fftwf_complex*>(&output[0]), 
													FFTW_ESTIMATE);
            fftwf_execute(plan);
            fftwf_destroy_plan(plan);
        }
        else{
            fftw_plan plan = fftw_plan_dft_r2c_1d(FFT_SIZE, 
												  (double*)input, 
												  reinterpret_cast<fftw_complex*>(&output[0]), 
												  FFTW_ESTIMATE);
            fftw_execute(plan);
            fftw_destroy_plan(plan);
        }
    }
    virtual void iFFT(LauraComplex* input, DATA_Array &output, int iFFT_SIZE){
        if(sizeof(DATA) == 4){
            fftwf_plan plan = fftwf_plan_dft_c2r_1d(iFFT_SIZE, 
													reinterpret_cast<fftwf_complex*>(&input[0]), 
													(float*)output, 
													FFTW_BACKWARD);
            fftwf_execute(plan);
            fftwf_destroy_plan(plan);
        }
        else{
            fftw_plan plan = fftw_plan_dft_c2r_1d(iFFT_SIZE, 
												  reinterpret_cast<fftw_complex*>(&input[0]), 
												  (double*)output, 
												  FFTW_BACKWARD);
            fftw_execute(plan);
            fftw_destroy_plan(plan);
        }
    }
};

#endif // LAURAFFTW_H

