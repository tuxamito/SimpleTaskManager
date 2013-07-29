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
    explicit SimpleTaskListWindow(QWidget *parent = 0);
    ~SimpleTaskListWindow();
    
protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void showOptions();
    void addTask();
    void createTask(QString);
    void loadInitData();
    void deleteTask(simpleTaskListWidget*);

private:
    Ui::SimpleTaskListWindow *ui;
    void addTaskToList(SimpleTask* task);
    SimpleTaskManager _stm;
};

#endif // SIMPLETASKLISTWINDOW_H
