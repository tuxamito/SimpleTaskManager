#ifndef SIMPLETASKINFOWIDGET_H
#define SIMPLETASKINFOWIDGET_H

#include <QWidget>
#include <QString>
#include <QDateTime>

#include "simpletask.h"

namespace Ui {
class SimpleTaskInfoWidget;
}

class SimpleTaskInfoWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit SimpleTaskInfoWidget(SimpleTask *st, QWidget *parent = 0);
    ~SimpleTaskInfoWidget();
    
    void setHeading(QString heading);

//public slots:

private slots:
    void accept();
    void cancel();
    void loadInfo();
    void changeTaskDone(bool done);
    void changeStartEnable(bool enable);
    void changedCreation(QDateTime newdatetime);

signals:
    void closeInfo();
    void closeInfoAccept();

private:
    Ui::SimpleTaskInfoWidget *ui;

    SimpleTask *_st;
};

#endif // SIMPLETASKINFOWIDGET_H
