#ifndef PRIORITYINDICATOR_H
#define PRIORITYINDICATOR_H

#include <QWidget>
#include <QPaintEvent>
#include <QColor>

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

    void setBorder(unsigned int border);
    unsigned int border();

    void setPriority(unsigned int priority);
    unsigned int priority();

private:
    Ui::PriorityIndicator *ui;
    unsigned int _border;
    unsigned int _priority;

    QColor getColor();
};

#endif // PRIORITYINDICATOR_H
