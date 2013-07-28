#include "simpletasklistwidget.h"
#include "ui_simpletasklistwidget.h"

#include <QMenu>
#include <QDebug>

simpleTaskListWidget::simpleTaskListWidget(QListWidgetItem *qlwi, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::simpleTaskListWidget)
{
    _task = NULL;
    _expanded = false;
    _qlwi = qlwi;

    ui->setupUi(this);

    this->grabGesture(Qt::TapAndHoldGesture);

    //this->setMouseTracking(true);
    installEventFilter(this);

#ifdef ANDROID
    int size = ui->label->height() - 4;
    QString style("QCheckBox::indicator { width: " + QString::number(size) + "px; height: " + QString::number(size) + "px; }");
    ui->checkDone->setStyleSheet(style);
#endif

    this->redraw();
}

simpleTaskListWidget::~simpleTaskListWidget()
{
    delete ui;
}

bool simpleTaskListWidget::event(QEvent *event)
{
    if (event->type() == QEvent::Gesture)
    {
        return gestureEvent(static_cast<QGestureEvent*>(event));
    }
    else if(event->type() == QEvent::ContextMenu)
    {
        return mouseEvent(static_cast<QMouseEvent*>(event));
    }

    return QWidget::event(event);
}

bool simpleTaskListWidget::mouseEvent(QMouseEvent *event)
{
    if(event->type() == QEvent::ContextMenu)
    {
        showMenu(0, 0);
    }

    return true;
}

bool simpleTaskListWidget::gestureEvent(QGestureEvent *event)
{
    if(event->gesture(Qt::TapAndHoldGesture))
    {
        showMenu(0, 0);
    }

    return true;
}

void simpleTaskListWidget::showMenu(int x, int y)
{
    QMenu *menu = new QMenu(this);
    menu->addAction(new QAction("New",this));
    menu->addAction(new QAction("Edit",this));
    menu->addAction(new QAction("Delete",this));
    menu->exec(QPoint(x, y));
}

QListWidgetItem *simpleTaskListWidget::myQLWI()
{
    return _qlwi;
}

void simpleTaskListWidget::redraw()
{
    if(_expanded)
        ui->buttonExpand->setIcon(QIcon(":/icons/arrow-up"));
    else
        ui->buttonExpand->setIcon(QIcon(":/icons/arrow-down"));

    if(_task)
    {
        ui->checkDone->setChecked(_task->done());
        if(_task->done())
        {
            QFont f = ui->label->font();
            f.setStrikeOut(true);
            ui->label->setFont(f);
        }
        else
        {
            QFont f = ui->label->font();
            f.setStrikeOut(false);
            ui->label->setFont(f);
        }
        ui->label->setText(QString::fromUtf8(_task->name().c_str()));
    }
    else
    {
        ui->label->setText("");
        ui->checkDone->setChecked(false);
    }

}

void simpleTaskListWidget::setTask(SimpleTask *task)
{
    _task = task;
    this->redraw();
}

SimpleTask *simpleTaskListWidget::task()
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

void simpleTaskListWidget::changeTaskDone(bool done)
{
    if(done)
    {
        _task->setDone(DONE);
    }
    else
    {
        _task->setDone(NOTDONE);
    }

    this->redraw();
}

void simpleTaskListWidget::deleteTask()
{
    emit deleteTask(this);
}
