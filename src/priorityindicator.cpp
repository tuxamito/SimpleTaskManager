#include "priorityindicator.h"
#include "ui_priorityindicator.h"

#include <QPainter>

PriorityIndicator::PriorityIndicator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PriorityIndicator)
{
    ui->setupUi(this);
    _border = 1;
    _priority = 0;
}

PriorityIndicator::~PriorityIndicator()
{
    delete ui;
}

void PriorityIndicator::paintEvent(QPaintEvent *)
{
    int totalHeight = height()-(2*_border);
    int totalWidth = width()-(2*_border);

    int barHeight = (int)((((float)totalHeight) * ((float)_priority)) / 100.0);
    int offset = totalHeight-barHeight;

    QPainter painter1(this);
    painter1.setBrush(this->getColor());
    painter1.setPen(Qt::NoPen);
    painter1.drawRect(_border, _border+offset, totalWidth, barHeight);

    QPainter painter2(this);
    painter2.drawRect(_border, _border, width()-(2*_border), height()-(2*_border));
}

void PriorityIndicator::setBorder(unsigned int border)
{
    _border = border;
}

unsigned int PriorityIndicator::border()
{
    return _border;
}

void PriorityIndicator::setPriority(unsigned int priority)
{
    if(priority>100)
    {
        _priority = 100;
    }
    else
    {
        _priority = priority;
    }
}

unsigned int PriorityIndicator::priority()
{
    return _priority;
}

QColor PriorityIndicator::getColor()
{
    QColor c;
    int eval = _priority / 10;

    switch(eval)
    {
    case 0:
        c = QColor(0, 42, 255, 255);
        break;
    case 1:
        c = QColor(0, 144, 255, 255);
        break;
    case 2:
        c = QColor(0, 255, 255, 255);
        break;
    case 3:
        c = QColor(0, 255, 144, 255);
        break;
    case 4:
        c = QColor(0, 255, 42, 255);
        break;
    case 5:
        c = QColor(42, 255, 0, 255);
        break;
    case 6:
        c = QColor(144, 255, 0, 255);
        break;
    case 7:
        c = QColor(255, 255, 0, 255);
        break;
    case 8:
        c = QColor(255, 144, 0, 255);
        break;
    case 9:
        c = QColor(255, 42, 0, 255);
        break;
    case 10:
        c = QColor(255, 0, 0, 255);
        break;
    default:
        c = QColor(0, 0, 0, 0);
        break;
    }

    return c;
}
