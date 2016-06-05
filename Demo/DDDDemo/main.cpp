#include "wnd_main.h"

#include <QApplication>
#include <QTextCodec>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    w.showMaximized();

    return a.exec();
}
