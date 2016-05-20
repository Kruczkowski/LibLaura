#include "spectrumplot.h"

SpectrumPlot::SpectrumPlot(QCustomPlot* model, int xMin, int xMax, int yMin, int yMax, int xSize,   int ySize)
    : Plot(model, xMin, xMax, yMin, yMax, xSize, ySize) {
    this->modelPlot->yAxis->setLabel("Amp. [dB]");
    this->modelPlot->xAxis->setLabel("Freq. [Hz]");
    this->initialize();
}

void SpectrumPlot::initialize(){
    for(int i=0;i<xSize;i++){
        this->xVector[i] = i*(44100/(xSize*2-1));
    }
    for(int i=0;i<ySize;i++){
        this->yVector[i] = 0;
    }
    this->modelPlot->addGraph();
}

void SpectrumPlot::setData(DATA *data){
    for (int i=0; i<ySize; i++){
        yVector[i] = log10(data[i]);
    }
    this->refresh();
}
