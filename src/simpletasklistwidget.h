#ifndef SIMPLETASKLISTWIDGET_H
#define SIMPLETASKLISTWIDGET_H

#include <QWidget>
#include <QListWidgetItem>
#include <QEvent>
#include <QGestureEvent>
#include <QMouseEvent>
#include <QPoint>

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
    void showOptions();

signals:
    void deleteTask(simpleTaskListWidget *);
    void showInfo(simpleTaskListWidget *);

private:
    bool event(QEvent *event);
    bool mouseEvent(QMouseEvent *event);
    bool gestureEvent(QGestureEvent *event);

    void showMenu(int x, int y);

    Ui::simpleTaskListWidget *ui;
    SimpleTask *_task;

    QListWidgetItem * _qlwi;

    bool _expanded;

    QPoint _menuPos;
};

#endif // SIMPLETASKLISTWIDGET_H
