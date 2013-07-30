#ifndef SIMPLETASKINFOWINDOW_H
#define SIMPLETASKINFOWINDOW_H

#include <QWidget>

#include "simpletask.h"
#include "simpletasklistwidget.h"

namespace Ui {
class SimpleTaskInfoWindow;
}

class SimpleTaskInfoWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit SimpleTaskInfoWindow(simpleTaskListWidget *tw, QWidget *parent = 0);
    ~SimpleTaskInfoWindow();
    
private slots:
    void accept();

private:
    Ui::SimpleTaskInfoWindow *ui;

    void loadInfo();
    simpleTaskListWidget *_tw;
};

#endif // SIMPLETASKINFOWINDOW_H
