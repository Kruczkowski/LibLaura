#ifndef SPECTRUMPLOT_H
#define SPECTRUMPLOT_H

#include "plot.h"

class SpectrumPlot : public Plot
{
public:
    SpectrumPlot(QCustomPlot *model, int xMin, int xMax, int yMin, int yMax, int xSize, int ySize);
    void setData(DATA*);

protected:
    virtual void initialize();
};

#endif // SPECTRUMPLOT_H
