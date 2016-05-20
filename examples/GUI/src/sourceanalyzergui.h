#ifndef SOURCEANALYZERGUI_H
#define SOURCEANALYZERGUI_H

#include <QMainWindow>
#include <QStringList>
#include <QStringListModel>
#include <QFileDialog>
#include <QMessageBox>
#include <QTimer>
#include <QTime>
#include "plot/qcustomplot/qcustomplot.h"
#include "plot/dynamicplot.h"
#include "plot/correlationplot.h"
#include "plot/spectrumplot.h"
#include "plot/circleplot.h"

#include <math.h>

#include "laura.h"

namespace Ui {
class SourceAnalyzerGUI;
}

class SourceAnalyzerGUI : public QMainWindow
{
    Q_OBJECT
    class Callback : public LauraCallback{

    public:
        DATA
        TDOA_result,
        ITD_result,
        ILD_result;

        DATA_Array
        GCCPHAT_result,
        rightSpectrum,
        leftSpectrum;

        double time;

        virtual void provider(CallbackResult* result){
            if(!result->get(TDOA, TDOA_result)) std::cout<<"Error with CallbackResult: TDOA"<<std::endl;
            if(!result->get(ITD, ITD_result)) std::cout<<"Error with CallbackResult: ITD"<<std::endl;
            if(!result->get(ILD, ILD_result)) std::cout<<"Error with CallbackResult: ILD"<<std::endl;
            if(!result->get(CORRELATION, GCCPHAT_result)) std::cout<<"Error with CallbackResult: GCCPHAT"<<std::endl;
            if(!result->get(SPECTRUM, rightSpectrum, leftSpectrum)) std::cout<<"Error with CallbackResult: SPECTRUM"<<std::endl;
            time = result->getTime();
        }
    };
public:
    explicit SourceAnalyzerGUI(QWidget *parent = 0);
    void setFilePath(char* path);
    Laura* laura;
    Callback* callback;
    ~SourceAnalyzerGUI();

private slots:

    void on_source_list_pressed(const QModelIndex &index);
    void on_pushButton_clicked();
    void on_start_file_button_clicked();
    void on_start_device_button_clicked();
    void on_output_device_list_pressed(const QModelIndex &index);
    void on_input_device_list_pressed(const QModelIndex &index);
    void on_stop_button_clicked();
    void errorString(QString);

private:
    Ui::SourceAnalyzerGUI *ui;
    QStringListModel *sourceListModel;
    QStringListModel *devicesListModel;
    QString filename;
    int timerId;
    int outputDeviceNumber = 0, inputDeviceNumber = 0;
    CorrelationPlot *correlationPlot;
    SpectrumPlot *leftSpectrumPlot, *rightSpectrumPlot;
    CirclePlot *circlePlot;
    DynamicPlot *dynamicPlot;

    void timerEvent(QTimerEvent *event);
    static void OperationOnStream(double *buff);
    void stopTimer();
};

#endif // SOURCEANALYZERGUI_H
