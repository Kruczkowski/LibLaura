#include "sourceanalyzergui.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SourceAnalyzerGUI w;
    if(argc > 1)
        w.setFilePath(argv[1]);
    w.show();

    return a.exec();
}
