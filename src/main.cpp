#include <QApplication>

#include "mainscreen.h"
#include "simpletasklistwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainScreen w;
    //SimpleTaskListWindow w;

#ifdef ANDROID
    w.showFullScreen();
#else
    w.show();
#endif

    return a.exec();
}
