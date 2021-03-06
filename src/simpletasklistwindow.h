#ifndef SIMPLETASKLISTWINDOW_H
#define SIMPLETASKLISTWINDOW_H

#include <QWidget>

#include "simpletaskmanager.h"
#include "simpletasklistwidget.h"

namespace Ui {
class SimpleTaskListWindow;
}

class SimpleTaskListWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit SimpleTaskListWindow(SimpleTaskManager *stm, QWidget *parent = 0);
    ~SimpleTaskListWindow();
    
public slots:
    void addTaskToView(SimpleTask* task);
    void setCurrent(int row);
    void update();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void showOptions();
    void addTask();
    void deleteTask(simpleTaskListWidget*);
    void showInfo(simpleTaskListWidget *);
    void showMenu(simpleTaskListWidget *);

signals:
    void newTask();
    void showTaskInfo(simpleTaskListWidget*);
    void showTaskMenu(simpleTaskListWidget*);

private:
    Ui::SimpleTaskListWindow *ui;
    SimpleTaskManager *_stm;
};

#endif // SIMPLETASKLISTWINDOW_H
