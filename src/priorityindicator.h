#ifndef PRIORITYINDICATOR_H
#define PRIORITYINDICATOR_H

#include <QWidget>
#include <QPaintEvent>

namespace Ui {
class PriorityIndicator;
}

class PriorityIndicator : public QWidget
{
    Q_OBJECT
    
public:
    explicit PriorityIndicator(QWidget *parent = 0);
    ~PriorityIndicator();
    void paintEvent(QPaintEvent *);

private:
    Ui::PriorityIndicator *ui;
};

#endif // PRIORITYINDICATOR_H
