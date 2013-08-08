#include "priorityindicator.h"
#include "ui_priorityindicator.h"

#include <QPainter>

PriorityIndicator::PriorityIndicator(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PriorityIndicator)
{
    ui->setupUi(this);
}

PriorityIndicator::~PriorityIndicator()
{
    delete ui;
}

void PriorityIndicator::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.setBrush(QColor(255, 0, 0, 255));
    painter.drawRect(1, 1, width()-2, height()-2);
}
