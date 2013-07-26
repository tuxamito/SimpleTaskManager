#ifndef SIMPLETASKLISTWIDGET_H
#define SIMPLETASKLISTWIDGET_H

#include <QWidget>
#include <QListWidgetItem>

#include "simpletask.h"

namespace Ui {
class simpleTaskListWidget;
}

class simpleTaskListWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit simpleTaskListWidget(QListWidgetItem *qlwi, QWidget *parent = 0);
    ~simpleTaskListWidget();
    
    void setTask(SimpleTask *task);
    SimpleTask *task();

    bool expanded();

    QListWidgetItem *myQLWI();

public slots:
    void redraw();

private slots:
    void changeTaskDone(bool done);
    void setExpanded(bool);
    void setExpandedToggle();
    void deleteTask();

signals:
    void deleteTask(simpleTaskListWidget *);

private:
    Ui::simpleTaskListWidget *ui;
    SimpleTask *_task;

    QListWidgetItem * _qlwi;

    bool _expanded;
};

#endif // SIMPLETASKLISTWIDGET_H
