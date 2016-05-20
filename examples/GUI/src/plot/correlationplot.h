#ifndef CORRELATIONPLOT_H
#define CORRELATIONPLOT_H

#include "plot.h"

class CorrelationPlot : public Plot
{
public:
    /**
     * @brief CorrelationPlot
     * @param model
     * @param xMin
     * @param xMax
     * @param yMin
     * @param yMax
     * @param ySize
     * @param zoom as integer
     */
    CorrelationPlot(QCustomPlot *model, int xMin, int xMax, int yMin, int yMax, int ySize, int zoom);
    void setData(DATA*);

protected:
    virtual void initialize();
    int zoom;
};

#endif // CORRELATIONPLOT_H
