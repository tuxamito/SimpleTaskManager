#ifndef SIMPLETASKLISTWIDGETMENU_H
#define SIMPLETASKLISTWIDGETMENU_H

#include <QWidget>
#include "simpletasklistwidget.h"

namespace Ui {
class SimpleTaskListWidgetMenu;
}

class SimpleTaskListWidgetMenu : public QWidget
{
    Q_OBJECT
    
public:
    explicit SimpleTaskListWidgetMenu(simpleTaskListWidget *tlw, QWidget *parent = 0);
    ~SimpleTaskListWidgetMenu();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void showTaskInfo(simpleTaskListWidget*);
    void showTaskAdd(simpleTaskListWidget*);

private slots:
    void showInfo();
    void addTask();
    void deleteTask();

private:
    Ui::SimpleTaskListWidgetMenu *ui;

    simpleTaskListWidget *_tlw;
};

#endif // SIMPLETASKLISTWIDGETMENU_H
