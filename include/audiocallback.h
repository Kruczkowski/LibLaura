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

#ifndef AUDIOCALLBACK_H
#define AUDIOCALLBACK_H

#include "lauracallback.h"
#include "lauratypes.h"

/**
 * @brief Contain shared field for buffer with one stream frame.
 *
 */
class AudioCallback{
    DATA_Array stream;
    int count;
public:
    AudioCallback(){
        count = 0;
    }
    ~AudioCallback(){
    }
    /**
     * @brief Method is called when reading stream frame.
     * @param stream frame
     */
    void setStream(DATA_Array buff){
        stream = buff;
        count++;
    }
    /**
     * @brief getStream
     * @return stream frame
     */
    DATA_Array getStream(){
        return stream;
    }
    int getFamreCounter(){
        return count;
    }
};
#endif // AUDIOCALLBACK_H

