
#include <string>
#include <cstdlib>

#include "laura.h"
#include "gccphat.h"

class Callback : public LauraCallback{
public:
    DATA
        TDOA_result,
        ILD_result,
        ITD_result;

    virtual void provider(CallbackResult* result){
        if(!(
                    result->get(TDOA, TDOA_result) &&
                    result->get(ILD, ILD_result) &&
                    result->get(ITD, ITD_result)
                    )){
            std::cout<<"Error with CallbackResult"<<std::endl;
        }
        else{
            std::cout << "Azimuth: " << TDOA_result << " deg, ILD: "
                      << ILD_result << " dB, ITD: " << ITD_result << " ?" << std::endl;
        }
    }
};

int main( int argc, char * argv[] ){

    if(argc < 2){
        std::cout << "Usage: localization_from_file <audio_file>" << std::endl;
        exit(1);
    }

	std::string pathToFile = argv[1];

    std::cout << "Input file name = " << pathToFile << std::endl;

    Laura laura(44100,              /* sample rate [Hz] */
                50,                 /* frame size [ms] */
                2,                  /* channels -> 2 (binaural) */
                0.175,              /* distance between microphones [m] -> 17.5cm */
                340,                /* speed of sound [m/s] */
                TDOA|CORRELATION);  /* flags */

    laura.setFlags(TDOA|ITD|ILD|CORRELATION|SPECTRUM);
    LauraEstimator* estimator = new GccPhat();
    laura.setEstimator(estimator);

    laura.showMessages(0);

    Callback* callback = new Callback();
    laura.setCallback((LauraCallback*&)callback, true);
    laura.setLogDir("./logs/", TDOA);

    laura.play(pathToFile, 0, 100);

    while(laura.isStreamRunning());

    delete callback;
}

