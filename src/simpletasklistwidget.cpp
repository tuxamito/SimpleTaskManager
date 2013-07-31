#include "simpletasklistwidget.h"
#include "ui_simpletasklistwidget.h"

#include <QMenu>
#include <QDebug>
#include <QGestureEvent>

simpleTaskListWidget::simpleTaskListWidget(QListWidgetItem *qlwi, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::simpleTaskListWidget)
{
    _task = NULL;
    _expanded = false;
    _qlwi = qlwi;

    ui->setupUi(this);

    this->grabGesture(Qt::TapAndHoldGesture);
    _menuPos.setX(0);
    _menuPos.setY(0);

#ifdef ANDROID
    QSize iSize(32, 32);

    int size = this->height() + 10;
    QString style("QCheckBox::indicator { width: " + QString::number(size) + "px; height: " + QString::number(size) + "px; }");
    ui->checkDone->setStyleSheet(style);

    ui->spacer1->changeSize(10, 5);
    ui->spacer2->changeSize(10, 5);
    ui->spacer3->changeSize(10, 5);
#else
    QSize iSize(16, 16);
    ui->spacer1->changeSize(5, 5);
    ui->spacer2->changeSize(5, 5);
    ui->spacer3->changeSize(0, 5);
#endif

    ui->buttonOptions->setIconSize(iSize);
    ui->buttonExpand->setIconSize(iSize);
    ui->buttonDelete->setIconSize(iSize);

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
    else if(event->type() == QEvent::MouseButtonPress)
    {
        return mouseEvent(static_cast<QMouseEvent*>(event));
    }

    return QWidget::event(event);
}

bool simpleTaskListWidget::mouseEvent(QMouseEvent *event)
{
    if(event->type() == QEvent::ContextMenu)
    {
        showMenu(_menuPos.x(), _menuPos.y());
    }
    else if(event->type() == QEvent::MouseButtonPress)
    {
        _menuPos = event->globalPos();
    }

    event->accept();

    return true;
}

bool simpleTaskListWidget::gestureEvent(QGestureEvent *event)
{
    if(const QGesture *g = event->gesture(Qt::TapAndHoldGesture))
    {
        if (g->state() == Qt::GestureFinished)
        {
            QPoint p = this->mapToGlobal(g->hotSpot().toPoint());
            showMenu(p.x(), p.y());
        }
    }

    event->accept();

    return true;
}

void simpleTaskListWidget::showMenu(int x, int y)
{
    emit showMenu(this);
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
            QFont f = ui->labelTaskName->font();
            f.setStrikeOut(true);
            ui->labelTaskName->setFont(f);
        }
        else
        {
            QFont f = ui->labelTaskName->font();
            f.setStrikeOut(false);
            ui->labelTaskName->setFont(f);
        }
        ui->labelTaskName->setText(QString::fromUtf8(_task->name().c_str()));
    }
    else
    {
        ui->labelTaskName->setText("");
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

void simpleTaskListWidget::showOptions()
{
    emit showInfo(this);
}
