#ifndef PLOT_H
#define PLOT_H

#include "qcustomplot/qcustomplot.h"
#include "lauratypes.h"
class Plot
{
public:
    Plot(QCustomPlot *model, int xMin, int xMax, int yMin, int yMax);
    Plot(QCustomPlot *model, int xMin, int xMax, int yMin, int yMax, int ySize);
    Plot(QCustomPlot *model, int xMin, int xMax, int yMin, int yMax, int xSize, int ySize);

protected:
    QCustomPlot *modelPlot;
    QVector<double> xVector, yVector;
    int xSize, ySize;

    void refresh();
    virtual void initialize()=0;
};
#endif // PLOT_H
