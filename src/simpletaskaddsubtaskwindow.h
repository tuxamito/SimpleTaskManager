#ifndef SIMPLETASKADDSUBTASKWINDOW_H
#define SIMPLETASKADDSUBTASKWINDOW_H

#include <QWidget>

#include "simpletasklistwidget.h"
#include "simpletaskinfowidget.h"
#include "simpletask.h"

namespace Ui {
class SimpleTaskAddSubTaskWindow;
}

class SimpleTaskAddSubTaskWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit SimpleTaskAddSubTaskWindow(simpleTaskListWidget *tw, QWidget *parent = 0);
    ~SimpleTaskAddSubTaskWindow();
    
signals:
    void newSubTask(simpleTaskListWidget*);

private slots:
    void acceptTask();
    void notAcceptTask();

private:
    Ui::SimpleTaskAddSubTaskWindow *ui;

    simpleTaskListWidget *_tw;
    SimpleTaskInfoWidget *_iw;
    SimpleTask *_st;
};

#endif // SIMPLETASKADDSUBTASKWINDOW_H
