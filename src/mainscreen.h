#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QGraphicsBlurEffect>

#include "simpletaskmanager.h"
#include "simpletasklistwindow.h"
#include "simpletaskaddwindow.h"
#include "simpletaskinfowindow.h"
#include "simpletasklistwidgetmenu.h"

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

    void showTaskInfo(simpleTaskListWidget*);
    void showTaskInfoMenu(simpleTaskListWidget*);
    void showAddSubTask(simpleTaskListWidget*);
    void showAddTask();
    void showTaskList();
    void showTaskListMenu(simpleTaskListWidget*);

    void createTask(QString);

private:
    Ui::mainScreen *ui;

    SimpleTaskListWindow *_stlw;
    SimpleTaskManager *_stm;
    SimpleTaskAddWindow *_staw;
    SimpleTaskInfoWindow *_stiw;
    SimpleTaskListWidgetMenu *_stmw;

    QGraphicsBlurEffect *_blur;

    simpleTaskListWidget *_showTaskInfo;
    simpleTaskListWidget *_showAddSubTask;
};

#endif // MAINSCREEN_H
