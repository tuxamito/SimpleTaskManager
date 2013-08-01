#ifndef SIMPLETASKADDWINDOW_H
#define SIMPLETASKADDWINDOW_H

#include <QWidget>

#include "simpletask.h"
#include "simpletaskinfowidget.h"

namespace Ui {
class SimpleTaskAddWindow;
}

class SimpleTaskAddWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit SimpleTaskAddWindow(SimpleTask *st, QWidget *parent = 0);
    ~SimpleTaskAddWindow();
    
signals:
    void newTask(SimpleTask*);

private slots:
    void acceptTask();
    void notAcceptTask();

private:
    Ui::SimpleTaskAddWindow *ui;

    SimpleTask *_st;
    SimpleTaskInfoWidget *_iw;
};

#endif // SIMPLETASKADDWINDOW_H
