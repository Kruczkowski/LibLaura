#include "dynamicplot.h"

DynamicPlot::DynamicPlot(QCustomPlot* model, int xMin, int xMax, int yMin, int yMax)
    : Plot(model, xMin, xMax, yMin, yMax) {
    this->initialize();
}

void DynamicPlot::initialize(){
    for(int i=0;i<xSize;i++){
        this->xVector[i] = i;
    }
    for(int i=0;i<ySize;i++){
        this->yVector[i] = 0;
    }
    this->modelPlot->addGraph();
}

void DynamicPlot::addValue(DATA value){
    for(int i=this->ySize-1; i>0; i--){
        this->yVector[i] = this->yVector[i-1];
    }
    this->yVector[0] = value;
    this->refresh();
}
