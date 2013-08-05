#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>
#include <QGraphicsBlurEffect>

#include "simpletaskmanager.h"
#include "simpletasklistwindow.h"
#include "simpletaskaddwindow.h"
#include "simpletaskaddsubtaskwindow.h"
#include "simpletaskinfowindow.h"
#include "simpletasklistwidgetmenu.h"
#include "simpletask.h"

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
    void showAddSubTaskToTask(simpleTaskListWidget*);
    void showAddTask();
    void showTaskList();
    void showTaskListMenu(simpleTaskListWidget*);

    void createTask(SimpleTask*);
    void createSubTask(simpleTaskListWidget*);

private:
    Ui::mainScreen *ui;

    SimpleTaskListWindow *_stlw;
    SimpleTaskManager *_stm;
    SimpleTaskAddWindow *_staw;
    SimpleTaskAddSubTaskWindow *_stsw;
    SimpleTaskInfoWindow *_stiw;
    SimpleTaskListWidgetMenu *_stmw;

    QGraphicsBlurEffect *_blur;

    simpleTaskListWidget *_showTaskInfo;
    simpleTaskListWidget *_showAddSubTask;
};

#endif // MAINSCREEN_H
