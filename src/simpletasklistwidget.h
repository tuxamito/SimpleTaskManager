#ifndef SIMPLETASKLISTWIDGET_H
#define SIMPLETASKLISTWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QEvent>
#include <QGestureEvent>
#include <QMouseEvent>
#include <QPoint>
#include <QString>

#include "simpletask.h"
#include "priorityindicator.h"

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
    void deleteTask();

private slots:
    void changeTaskDone(bool done);
    void setExpanded(bool);
    void setExpandedToggle();
    void showOptions();

    void changeDescription(QString description);

signals:
    void deleteTask(simpleTaskListWidget *);
    void showInfo(simpleTaskListWidget *);
    void showMenu(simpleTaskListWidget *);
    void updateList();

private:
    bool event(QEvent *event);
    bool mouseEvent(QMouseEvent *event);
    bool gestureEvent(QGestureEvent *event);
    void showMenu();

    Ui::simpleTaskListWidget *ui;

    SimpleTask *_task;
    QListWidgetItem *_qlwi;
    PriorityIndicator *_priorityW;

    unsigned int _subTaskLevel;

    bool _expanded;
};

#endif // SIMPLETASKLISTWIDGET_H
