#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>

#include "simpletaskmanager.h"
#include "simpletasklistwindow.h"

namespace Ui {
class mainScreen;
}

class mainScreen : public QWidget
{
    Q_OBJECT
    
public:
    explicit mainScreen(QWidget *parent = 0);
    ~mainScreen();

private:
    Ui::mainScreen *ui;

    SimpleTaskListWindow *_stlw;
    SimpleTaskManager *_stm;
};

#endif // MAINSCREEN_H
