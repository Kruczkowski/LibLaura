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

#include "lauralogger.h"
#include "lauramessenger.h"

/**
 * @brief LauraLogger::LauraLogger
 * @param pathToDir
 *      Dest path to save logs
 * @param flag
 *      Types of logs
 * @param frameSize
 *      Size of audio frame
 * @param samplingRate
 *      Sampling frequency
 */
LauraLogger::LauraLogger(std::string pathToDir, unsigned int flag, 
                         unsigned int frameSize, unsigned int samplingRate){
    this->pathToDir = pathToDir;
    this->flags = flag;
    this->BUFF_SIZE = nextPow2(frameSize);
    this->firstRunning = true;
    this->SAMPLING_RATE = samplingRate;
    this->fileNames = new std::string[6];
    fileNames[0] = "TDOA";
    fileNames[1] = "ITD";
    fileNames[2] = "ILD";
    fileNames[3] = "CORRELATION";
    fileNames[4] = "SPECTRUM";
    fileNames[5] = "STREAM";
}
LauraLogger::~LauraLogger(){
    close();
}

/**
 * @brief Sets log filename
 * @param flag
 *      Type of logs
 * @param fileName
 *      New filename
 */
void LauraLogger::setFileName(LauraFlag flag, std::string fileName){
    switch(flag){
        case TDOA:
            fileNames[0] = fileName;
        break;
        case ITD:
            fileNames[1] = fileName;
        break;
        case ILD:
            fileNames[2] = fileName;
        break;
        case CORRELATION:
            fileNames[3] = fileName;
        break;
        case SPECTRUM:
            fileNames[4] = fileName;
        break;
        case STREAM:
            fileNames[5] = fileName;
        break;
        default:
            LauraMessenger::printWarning("LauraLogger::setFileName: Undefined value.");
        break;

    }
}

/**
 * @brief initialize object
 */

void LauraLogger::init(){
    if(flags & TDOA){
        TDOA_logfile.open( (pathToDir+fileNames[0]+".log").c_str() );
    }
    if(flags & ITD){
        ITD_logfile.open( (pathToDir+fileNames[1]+".log").c_str() );
    }
    if(flags & ILD){
        ILD_logfile.open( (pathToDir+fileNames[2]+".log").c_str() );
    }
    if(flags & CORRELATION){
        CORR_logfile.open( (pathToDir+fileNames[3]+".log").c_str() );
    }
    if(flags & SPECTRUM){
        SPECTRUM_RIGHT_logfile.open( (pathToDir+fileNames[4]+"_1.log").c_str() );
        SPECTRUM_LEFT_logfile.open( (pathToDir+fileNames[4]+"_2.log").c_str() );
    }
    if(flags & STREAM){
        STREAM_wavfile = SndfileHandle( (pathToDir+fileNames[5]+".wav").c_str(),SFM_WRITE,SF_FORMAT_WAV|SF_FORMAT_DOUBLE, 2, SAMPLING_RATE);
    }
}

/**
 * @brief Writes log to file
 * @param result
 *      Results container
 * @param time
 *      Current time
 */
void LauraLogger::writeLogToFile(CallbackResult* result, double time){
    if(firstRunning){
        init();
        firstRunning = false;
    }
    if(flags & TDOA){
        DATA tdoa;
        result->get(TDOA, tdoa);
        TDOA_logfile << time << " " << tdoa << std::endl;
    }
    if(flags & ITD){
        DATA itd;
        result->get(ITD, itd);
        ITD_logfile << time << " " << itd << std::endl;
    }
    if(flags & ILD){
        DATA ild;
        result->get(ILD, ild);
        ILD_logfile << time << " " << ild << std::endl;
    }
    if(flags & CORRELATION){
        DATA_Array correlation;
        result->get(CORRELATION, correlation);
        CORR_logfile << time << ": ";
        for(int i=0; i<BUFF_SIZE*2-1; i++){
            CORR_logfile << correlation[i] << " ";
        }
        CORR_logfile << ";\n";
    }
    if(flags & SPECTRUM){
        DATA_Array right,left;
        result->get(SPECTRUM, right, left);
        SPECTRUM_RIGHT_logfile << time << ": ";
        SPECTRUM_LEFT_logfile << time << ": ";
        for(int i=0;i<BUFF_SIZE*2-1;i++){
            SPECTRUM_RIGHT_logfile << right[i] << " ";
            SPECTRUM_LEFT_logfile << left[i] << " ";
        }
        SPECTRUM_RIGHT_logfile << ";\n";
        SPECTRUM_LEFT_logfile << ";\n";
    }
    if(flags & STREAM){
        DATA_Array stream;
        result->get(STREAM, stream);
        STREAM_wavfile.write(stream,BUFF_SIZE*2);
    }
}

/**
 * @brief Closes all discriptors
 */
void LauraLogger::close(){
    if(flags & TDOA){
        TDOA_logfile.close();
    }
    if(flags & ITD){
        ITD_logfile.close();
    }
    if(flags & ILD){
        ILD_logfile.close();
    }
    if(flags & CORRELATION){
        CORR_logfile.close();
    }
    if(flags & SPECTRUM){
        SPECTRUM_RIGHT_logfile.close();
        SPECTRUM_LEFT_logfile.close();
    }
}

