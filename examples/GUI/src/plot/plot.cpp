#include "plot.h"

Plot::Plot(QCustomPlot *model, int xMin, int xMax, int yMin, int yMax)
    : modelPlot(model), xSize(xMax - xMin), ySize(yMax - yMin) {
    this->modelPlot->xAxis->setRange(xMin, xMax);
    this->modelPlot->yAxis->setRange(yMin, yMax);

    this->xVector.resize(this->xSize);
    this->yVector.resize(this->ySize);
}
Plot::Plot(QCustomPlot *model, int xMin, int xMax, int yMin, int yMax, int ySize)
    : modelPlot(model), xSize(xMax - xMin), ySize(ySize) {
    this->modelPlot->xAxis->setRange(xMin, xMax);
    this->modelPlot->yAxis->setRange(yMin, yMax);

    this->xVector.resize(this->xSize);
    this->yVector.resize(this->ySize);
}
Plot::Plot(QCustomPlot *model, int xMin, int xMax, int yMin, int yMax, int xSize, int ySize)
    : modelPlot(model), xSize(xSize), ySize(ySize) {
    this->modelPlot->xAxis->setRange(xMin, xMax);
    this->modelPlot->yAxis->setRange(yMin, yMax);

    this->xVector.resize(this->xSize);
    this->yVector.resize(this->ySize);
}

void Plot::refresh(){
    this->modelPlot->graph(0)->setData(this->xVector, this->yVector);
    this->modelPlot->replot();
}
