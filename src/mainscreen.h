#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>

#include "simpletaskmanager.h"
#include "simpletasklistwindow.h"
#include "simpletaskaddwindow.h"

namespace Ui {
class mainScreen;
}

class mainScreen : public QWidget
{
    Q_OBJECT
    
public:
    explicit mainScreen(QWidget *parent = 0);
    ~mainScreen();

private slots:
    void loadInitData();
    void showAddTask();
    void showTaskList();

    void createTask(QString);

private:
    Ui::mainScreen *ui;

    SimpleTaskListWindow *_stlw;
    SimpleTaskManager *_stm;
    SimpleTaskAddWindow *_staw;
};

#endif // MAINSCREEN_H
