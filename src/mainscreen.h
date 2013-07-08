#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>

#include "simpletaskmanager.h"
#include "simpletasklistwidget.h"

namespace Ui {
class mainScreen;
}

class mainScreen : public QWidget
{
    Q_OBJECT
    
public:
    explicit mainScreen(QWidget *parent = 0);
    ~mainScreen();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void showOptions();
    void addTask();
    void createTask(QString);

private:
    Ui::mainScreen *ui;

    SimpleTaskManager _tm;
};

#endif // MAINSCREEN_H
