#include "circleplot.h"

CirclePlot::CirclePlot(QCustomPlot* model, int xMin, int xMax, int yMin, int yMax, int xSize, int ySize)
    : Plot(model, xMin, xMax, yMin, yMax, xSize, ySize) {
    this->initialize();
}

void CirclePlot::initialize(){
    QVector<double> x_circle(90), y_circle(90);
    for (int i=0; i< 90; i++){
      x_circle[i] = sin(i)*90;
      y_circle[i] = cos(i)*90;
    }
    for(int i=0;i<2;i++){
        this->xVector[i] = 0;
    }
    for(int i=0;i<2;i++){
        this->yVector[i] = 0;
    }
    modelPlot->addGraph();
    modelPlot->graph(0)->setData(xVector, yVector);

    modelPlot->addGraph();
    modelPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    modelPlot->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 1));
    modelPlot->graph(1)->setData(x_circle, y_circle);
}

void CirclePlot::addValue(DATA value){
    xVector[0] = 0;
    xVector[1] = cos(value/180*M_PI)*90;
    yVector[0] = 0;
    yVector[1] = sin(value/180*M_PI)*90;
    this->refresh();
}
