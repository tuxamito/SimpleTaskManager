#ifndef ADDTASKDIALOG_H
#define ADDTASKDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class addTaskDialog;
}

class addTaskDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit addTaskDialog(QWidget *parent = 0);
    ~addTaskDialog();
    
signals:
    void newTask(QString);

private slots:
    void acceptWork();

private:
    Ui::addTaskDialog *ui;
};

#endif // ADDTASKDIALOG_H
