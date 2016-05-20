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

#ifndef CALLBACKRESULT_H
#define CALLBACKRESULT_H

#include <iostream>
#include <cstring>
#include <map>
#include <typeinfo>

#include "lauratypes.h"

/**
 * @brief It's returned as a result of analysis.
 */

class CallbackResult{
 
 	union DataUnion{
        DATA_Array array2D[2];
        DATA_Array array;
        DATA value;
        DataUnion(){}
        ~DataUnion(){}
    } ;
    struct LauraResultStruct{
        DataUnion data;
        LauraFlag type;
        LauraResultStruct(){}
        ~LauraResultStruct(){}
    };
    double time;
    bool isDownloaded, isUploaded;

public:
    CallbackResult();
    ~CallbackResult();

    std::map<LauraFlag, LauraResultStruct> results;

    void initialize(unsigned int flags, int FRAME_SIZE, short CHANNELS);
    void clear();

    void add(DATA input, LauraFlag type);
    void add(DATA_Array input, LauraFlag type);
    void add(DATA_Array input_1, DATA_Array input_2, LauraFlag type);
    void setTime(double time);

    int get(LauraFlag type, DATA &output);
    int get(LauraFlag type, DATA_Array &output);
    int get(LauraFlag type, DATA_Array &output_1, DATA_Array &output_2);
    double getTime();
};

#endif // CALLBACKRESULT_H
