#ifndef SIMPLETASKADDWINDOW_H
#define SIMPLETASKADDWINDOW_H

#include <QWidget>

namespace Ui {
class SimpleTaskAddWindow;
}

class SimpleTaskAddWindow : public QWidget
{
    Q_OBJECT
    
public:
    explicit SimpleTaskAddWindow(QWidget *parent = 0);
    ~SimpleTaskAddWindow();
    
signals:
    void newTask(QString);

private slots:
    void acceptTask();

private:
    Ui::SimpleTaskAddWindow *ui;
};

#endif // SIMPLETASKADDWINDOW_H
