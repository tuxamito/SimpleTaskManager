#include <QApplication>

#include "mainscreen.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainScreen w;

#ifdef ANDROID
    w.showFullScreen();
#else
    w.show();
#endif

    return a.exec();
}
