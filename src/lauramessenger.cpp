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

#include "lauramessenger.h"

unsigned int LauraMessenger::flags = ERROR;

/**
 * @brief Prints information
 * @param message
 *      Information message
 */
void LauraMessenger::printInfo(std::string message){
    if(LauraMessenger::flags & INFO){
        std::cout << message << std::endl;
    }
}

/**
 * @brief Prints warning
 * @param message
 *      Warning message
 */
void LauraMessenger::printWarning(std::string message){
    if(LauraMessenger::flags & WARNING){
        std::cout << message << std::endl;
    }
}

/**
 * @brief Prints error
 * @param message
 *      Error message
 */
void LauraMessenger::printError(std::string message){
    if(LauraMessenger::flags & ERROR){
        std::cout << message << std::endl;
    }
}

/**
 * @brief Sets flags
 * @param flags
 */
void LauraMessenger::resetFlags(unsigned int _flags){
    LauraMessenger::flags = _flags;
}

