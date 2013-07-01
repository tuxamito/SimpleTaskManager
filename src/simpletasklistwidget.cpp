#include "simpletasklistwidget.h"
#include "ui_simpletasklistwidget.h"

simpleTaskListWidget::simpleTaskListWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::simpleTaskListWidget)
{
    _task = NULL;
    _expanded = false;

    ui->setupUi(this);

    this->redraw();
}

simpleTaskListWidget::~simpleTaskListWidget()
{
    delete ui;
}

void simpleTaskListWidget::redraw()
{
    if(_expanded)
        ui->buttonExpand->setIcon(QIcon(":/icons/arrow-up"));
    else
        ui->buttonExpand->setIcon(QIcon(":/icons/arrow-down"));

    if(_task)
    {
        ui->label->setText(QString::fromUtf8(_task->name().c_str()));

        ui->checkDone->setChecked(_task->done());
    }
}

void simpleTaskListWidget::setTask(simpleTask *task)
{
    _task = task;

    this->redraw();
}

simpleTask *simpleTaskListWidget::task()
{
    return _task;
}

bool simpleTaskListWidget::expanded()
{
    return _expanded;
}

void simpleTaskListWidget::setExpanded(bool expanded)
{
    _expanded = expanded;
    this->redraw();
}

void simpleTaskListWidget::setExpandedToggle()
{
    this->setExpanded(!_expanded);
}

void simpleTaskListWidget::changeTaskDone(bool)
{

}
