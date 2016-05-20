#include "sourceanalyzergui.h"
#include "ui_sourceanalyzergui.h"
#include <gccphat.h>
#include <QThread>
#include <QMessageBox>
#include <cstdlib>
#include <algorithm>
#include <cmath>


QTime toQTime(double time){
    int ms,s,m,h;
    ms = (int)time;
    s  = ms / 1000;
    ms %= 1000;
    m  = s  / 60;
    s  %= 60;
    h  = m  / 60;
    m  %= 60;
    return QTime(h,m,s,ms);
}

SourceAnalyzerGUI::SourceAnalyzerGUI(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SourceAnalyzerGUI){
    /* setup the UI */
    ui->setupUi(this);

    /* initialization of audio data*/
    int SAMPLING_RATE = 44100;
    float FRAME_LENGHT = 50;
    int FRAME_SIZE = FRAME_LENGHT*SAMPLING_RATE/1000;
    int CHANNELS = 2;

    laura = new Laura(SAMPLING_RATE, FRAME_LENGHT, CHANNELS,0.175,340, TDOA|CORRELATION|SPECTRUM|STREAM|ILD|ITD );
    GccPhat* estimator = new GccPhat();
    laura->setEstimator(estimator);
    callback = new Callback();
    laura->showMessages(ALLMESSAGES);
    laura->setCallback((LauraCallback*)this->callback, 1);
    laura->setLogDir("./logs/",TDOA|CORRELATION);

    sourceListModel = new QStringListModel( this );
    devicesListModel = new QStringListModel( this );
    filename = "";

    /* declaration and initialization elements of UI*/
    QStringList sourceQList;
    sourceQList << "Device" << "File";

    std::string* deviceList = laura->audio->getDeviceList();
    QStringList deviceQList;
    for(int count = 0 ; count < laura->audio->getDeviceCount() ; count++ ){
        deviceQList.append( QString::fromStdString(deviceList[count]));
    }
    sourceListModel->setStringList( sourceQList );
    devicesListModel->setStringList( deviceQList );
    ui->source_list->setModel( sourceListModel );
    ui->input_device_list->setModel( devicesListModel );
    ui->output_device_list->setModel( devicesListModel );

    ui->file_box->setVisible(false);
    ui->device_box->setVisible(true);

    /* initialization plots */
    int sizeOfBuffe = laura->getSizeOfBuffer();
    correlationPlot = new CorrelationPlot(ui->correlation_plot, sizeOfBuffe*(-1), sizeOfBuffe, -1, 1, sizeOfBuffe*2,3);
    leftSpectrumPlot = new SpectrumPlot(ui->left_plot, 0, SAMPLING_RATE/2-FRAME_SIZE, 0, 10, FRAME_SIZE, FRAME_SIZE);
    rightSpectrumPlot = new SpectrumPlot(ui->right_plot, 0, SAMPLING_RATE/2-FRAME_SIZE, 0, 10, FRAME_SIZE, FRAME_SIZE);
    circlePlot = new CirclePlot(ui->circle_plot, -90, 90, -90, 90, 2, 2);
    dynamicPlot = new DynamicPlot(ui->dynamic_plot, 0, 100, -180, 180);

    /*initialization ID of timer*/
    timerId = 0;
}
SourceAnalyzerGUI::~SourceAnalyzerGUI(){
    delete ui;
}
void SourceAnalyzerGUI::on_source_list_pressed(const QModelIndex &index){
    const QAbstractItemModel * model = index.model();
    if(model->data(index, 0).toString() == "Device"){
        ui->file_box->setVisible(false);
        ui->device_box->setVisible(true);
    }
    else{
        ui->file_box->setVisible(true);
        ui->device_box->setVisible(false);
    }
}

//Click on button opens dialog to choose file.
void SourceAnalyzerGUI::on_pushButton_clicked(){
    QString filePath = QFileDialog::getOpenFileName(this, tr("Open File"),
                                                    "./",
                                                    tr("Audio Files (*.wav *.flac *.raw)"));
    ui->filename_text->setText(filePath);
    filename = filePath;
}
void SourceAnalyzerGUI::setFilePath(char* path){
    ui->file_box->setVisible(true);
    ui->device_box->setVisible(false);
    QString filePath(path);
    ui->filename_text->setText(filePath);
    filename = filePath;
    on_start_file_button_clicked();
}

void SourceAnalyzerGUI::timerEvent(QTimerEvent *event){

    if(!laura->isStreamRunning()){
        stopTimer();
    }

    ui->timeEdit->setTime(toQTime(callback->time));
    ui->angleText->setText("Angle: "+QString::number(callback->TDOA_result));
    ui->itdText->setText("ITD (us): "+QString::number(callback->ITD_result));
    ui->ildText->setText("ILD (dB): "+QString::number(callback->ILD_result));
    correlationPlot->setData(callback->GCCPHAT_result);
    rightSpectrumPlot->setData(callback->rightSpectrum);
    leftSpectrumPlot->setData(callback->leftSpectrum);
    circlePlot->addValue(callback->TDOA_result);
    dynamicPlot->addValue(callback->TDOA_result);
}

void SourceAnalyzerGUI::on_start_file_button_clicked(){

    if(timerId == 0){
        timerId = startTimer(100);
        laura->play(filename.toStdString().c_str(), outputDeviceNumber,50);
    }
    else{
        std::cout<<"Click stop or wait for end of playback"<<std::endl;
    }
}

void SourceAnalyzerGUI::on_start_device_button_clicked(){
    if(timerId == 0){
        laura->capture(outputDeviceNumber,50);
        timerId = startTimer(50);
    }
    else{
        std::cout<<"Click stop or wait for end of playback"<<std::endl;
    }
}

void SourceAnalyzerGUI::stopTimer(){
    if(timerId != 0){
        killTimer(timerId);
        timerId = 0;
    }
}

void SourceAnalyzerGUI::on_output_device_list_pressed(const QModelIndex &index){
    this->outputDeviceNumber = index.row();
}

void SourceAnalyzerGUI::on_input_device_list_pressed(const QModelIndex &index){
    this->inputDeviceNumber = index.row();
}

void SourceAnalyzerGUI::on_stop_button_clicked(){
    stopTimer();
    laura->stop();
}

void SourceAnalyzerGUI::errorString(QString error){
    this->stopTimer();
    QMessageBox box;
    box.setText(error);
    box.exec();
}

