#ifndef SIMPLETASKLISTWIDGET_H
#define SIMPLETASKLISTWIDGET_H

#include <QWidget>

namespace Ui {
class simpleTaskListWidget;
}

class simpleTaskListWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit simpleTaskListWidget(QWidget *parent = 0);
    ~simpleTaskListWidget();
    
private:
    Ui::simpleTaskListWidget *ui;
};

#endif // SIMPLETASKLISTWIDGET_H
