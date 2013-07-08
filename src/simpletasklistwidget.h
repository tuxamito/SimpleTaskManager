#ifndef SIMPLETASKLISTWIDGET_H
#define SIMPLETASKLISTWIDGET_H

#include <QWidget>

#include "simpletask.h"

namespace Ui {
class simpleTaskListWidget;
}

class simpleTaskListWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit simpleTaskListWidget(QWidget *parent = 0);
    ~simpleTaskListWidget();
    
    void setTask(SimpleTask *task);
    SimpleTask *task();

    bool expanded();

public slots:
    void redraw();

private slots:
    void changeTaskDone(bool);
    void setExpanded(bool);
    void setExpandedToggle();

private:
    Ui::simpleTaskListWidget *ui;

    SimpleTask *_task;

    bool _expanded;
};

#endif // SIMPLETASKLISTWIDGET_H
