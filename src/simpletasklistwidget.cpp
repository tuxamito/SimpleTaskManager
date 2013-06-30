#include "simpletasklistwidget.h"
#include "ui_simpletasklistwidget.h"

simpleTaskListWidget::simpleTaskListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::simpleTaskListWidget)
{
    ui->setupUi(this);
}

simpleTaskListWidget::~simpleTaskListWidget()
{
    delete ui;
}
