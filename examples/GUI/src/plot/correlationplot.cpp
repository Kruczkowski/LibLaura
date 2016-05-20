#include "correlationplot.h"

CorrelationPlot::CorrelationPlot(QCustomPlot* model, int xMin, int xMax, int yMin, int yMax, int ySize, int zoom)
    : Plot(model, xMin, xMax, yMin, yMax, ySize){
    this->zoom = 2<<(zoom-2);
    this->initialize();
}

void CorrelationPlot::initialize(){
    for(int i=xSize/(-2);i<xSize/2;i++){
        this->xVector[i+xSize/2] = i;
    }
    for(int i=0;i<ySize;i++){
        this->yVector[i] = 0;
    }
    this->modelPlot->addGraph();
}

void CorrelationPlot::setData(DATA *data){
    if(zoom<=0){
        for (int i=0; i<ySize; i++)
            yVector[i] = data[i];
    }
    else{
        int sizePart = ySize/(zoom*2);
        int begin = sizePart*(zoom-1);
        int end = sizePart*(zoom+1);
        for (int i=begin; i<end; i++){
            for(int j=0;j<zoom;j++)
                yVector[(i-begin)*zoom+j] = data[i];
        }
    }
    this->refresh();
}
