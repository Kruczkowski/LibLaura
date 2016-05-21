#include <string>
#include <cstdlib>
#include <sys/time.h>

#include "laura.h"

class Callback : public LauraCallback{
public:
    DATA
        TDOA_result;

    virtual void provider(CallbackResult* result){
        if(!( result->get(TDOA, TDOA_result) )){
            std::cout << "Error with CallbackResult" << std::endl;
        }
    }
};

int main( int argc, char * argv[] ){
    struct timeval  start, stop;
    int time, device;

    Laura* laura = new Laura(44100,              /* sample rate [Hz] */
                             11.6,               /* frame size [ms] */
                             2,                  /* channels -> 2 (binaural) */
                             0.175,              /* distance between microphones [m] -> 17.5cm */
                             340,                /* speed of sound [m/s] */
                             TDOA|CORRELATION);  /* flags */

    laura->showMessages(ALLMESSAGES);
 
 	Callback* callback = new Callback();
    laura->setCallback((LauraCallback*&)callback, false);
 
 	laura->setLogDir("./logs/",TDOA);
	std::string *deviceList = laura->audio->getDeviceList();

	std::cout << "Available devices:" << std::endl;
    for(int count = 0 ; count < laura->audio->getDeviceCount() ; count++ ){
		std::cout << count << ". " << deviceList[count] << std::endl;
    }
    if(laura->audio->getDeviceCount() > 1){
		std::cout << "Enter the number of the device: ";
		std::cin >> device;
    }else{
        device = 0;
    }

	std::cout << "Set time [seconds]: ";
	std::cin >> time;

	laura->capture(device, 100);
    gettimeofday(&start, NULL);

	while(stop.tv_sec-start.tv_sec < time){
        gettimeofday(&stop, NULL);
        usleep(1000);
		std::cout << "Azimuth: " << callback->TDOA_result << " deg" << std::endl;
    }

    laura->audio->stop();
    while(laura->isStreamRunning());
    delete callback;
    delete laura;

}

