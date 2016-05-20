#ifndef DYNAMICPLOT_H
#define DYNAMICPLOT_H

#include "plot.h"

class DynamicPlot : public Plot
{
public:
    DynamicPlot(QCustomPlot *model, int xMin, int xMax, int yMin, int yMax);
    void addValue(DATA);

protected:
    virtual void initialize();
};

#endif // DYNAMICPLOT_H
