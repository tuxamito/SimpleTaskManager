#include "simpletasklistwidget.h"
#include "ui_simpletasklistwidget.h"

#include "priorityindicator.h"

#include <QMenu>
#include <QDebug>
#include <QGestureEvent>

simpleTaskListWidget::simpleTaskListWidget(QListWidgetItem *qlwi, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::simpleTaskListWidget)
{
    _task = NULL;
    _subTaskLevel = 0;
    _expanded = false;
    _qlwi = qlwi;

    ui->setupUi(this);

    this->grabGesture(Qt::TapAndHoldGesture);

#ifdef ANDROID
    QSize iSize(32, 32);

    int size = this->height() + 8;
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

    PriorityIndicator *priorityW = new PriorityIndicator(this);
    ui->horizontalLayout_2->addWidget(priorityW);

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
        showMenu();
    }
    else if(event->type() == QEvent::MouseButtonPress)
    {
        //Keep for future menu position...
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
            //Keep in case menus work in android in the future...
            //QPoint p = this->mapToGlobal(g->hotSpot().toPoint());
            showMenu();
        }
    }

    event->accept();

    return true;
}

void simpleTaskListWidget::showMenu()
{
    emit showMenu(this);
}

QListWidgetItem *simpleTaskListWidget::myQLWI()
{
    return _qlwi;
}

void simpleTaskListWidget::redraw()
{
    int nt = 0;
    int nd = 0;
    QString stringNTD;

    if(_expanded)
        ui->buttonExpand->setIcon(QIcon(":/icons/arrow-down"));
    else
        ui->buttonExpand->setIcon(QIcon(":/icons/arrow-up"));

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

        _task->subTasksFigures(&nt, &nd);
        if(nt > 0)
        {
            stringNTD = " (" + QString::number(nd) + "/" + QString::number(nt) + ")";
            ui->progressBar->setMinimum(0);
            ui->progressBar->setMaximum(nt);
            ui->progressBar->setValue(nd);
            ui->progressBar->setVisible(true);
        }
        else
        {
            stringNTD = "";
            ui->progressBar->setVisible(false);
        }

        ui->labelTaskName->setText(QString::fromUtf8(_task->name().c_str()) + stringNTD);
        this->changeDescription(QString::fromUtf8(_task->description().c_str()));
        ui->buttonExpand->setEnabled(!_task->getSubTasks()->empty());

        ui->spacerSubTask->changeSize(_task->level() * 20, 5);
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
    this->_expanded = _task->expanded();
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
    _task->setExpanded(_expanded);
    this->redraw();
    emit updateList();
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
    emit updateList();
}

void simpleTaskListWidget::deleteTask()
{
    emit deleteTask(this);
    emit updateList();
}

void simpleTaskListWidget::showOptions()
{
    emit showInfo(this);
}

void simpleTaskListWidget::changeDescription(QString description)
{
    ui->labelTaskDescription->setText(description.trimmed());
    ui->labelTaskDescription->setVisible(description.trimmed() != "");
}
