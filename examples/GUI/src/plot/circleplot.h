#ifndef CIRCLEPLOT_H
#define CIRCLEPLOT_H

#include "plot.h"

class CirclePlot : public Plot
{
public:
    CirclePlot(QCustomPlot *model, int xMin, int xMax, int yMin, int yMax, int xSize, int ySize);
    void addValue(DATA);

protected:
    virtual void initialize();
};

#endif // CIRCLEPLOT_H
