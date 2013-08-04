#include "simpletasklistwindow.h"
#include "ui_simpletasklistwindow.h"

#include <QListWidgetItem>
#include <QCloseEvent>
#include <QDirIterator>
#include <QFile>
#include <QDebug>

#include "simpletaskcommon.h"
#include "simpletaskaddwindow.h"
#include "simpletaskoperations.h"

SimpleTaskListWindow::SimpleTaskListWindow(SimpleTaskManager *stm, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleTaskListWindow)
{
    ui->setupUi(this);
    _stm = stm;

    this->update();
}

SimpleTaskListWindow::~SimpleTaskListWindow()
{
    delete ui;
}

void SimpleTaskListWindow::update()
{
    ui->listTasks->clear();
    lst_t list = _stm->getTaskList();

    for(auto i = list.begin(); i != list.end(); ++i)
    {
        SimpleTask *t = (*i);
        this->addTaskToView(t);
    }
}

void SimpleTaskListWindow::showOptions()
{

}

void SimpleTaskListWindow::addTask()
{
    emit newTask();
}

void SimpleTaskListWindow::addTaskToView(SimpleTask* task)
{
    QListWidgetItem *nw = new QListWidgetItem;
    simpleTaskListWidget *nt = new simpleTaskListWidget(nw);

    ui->listTasks->insertItem(ui->listTasks->count(), nw);
    ui->listTasks->setItemWidget(nw, nt);

#ifdef ANDROID
    nw->setSizeHint(nt->sizeHint() + QSize(0, 18));
#else
    nw->setSizeHint(nt->sizeHint());
#endif

    nt->setTask(task);

    connect(nt, SIGNAL(showInfo(simpleTaskListWidget*)), this, SLOT(showInfo(simpleTaskListWidget*)));
    connect(nt, SIGNAL(deleteTask(simpleTaskListWidget*)), this, SLOT(deleteTask(simpleTaskListWidget*)));
    connect(nt, SIGNAL(showMenu(simpleTaskListWidget*)), this, SLOT(showMenu(simpleTaskListWidget*)));
    connect(nt, SIGNAL(updateList()), this, SLOT(update()));
}

void SimpleTaskListWindow::showMenu(simpleTaskListWidget *tw)
{
    ui->listTasks->setCurrentItem(tw->myQLWI());
    emit showTaskMenu(tw);
}

void SimpleTaskListWindow::showInfo(simpleTaskListWidget *tw)
{
    emit showTaskInfo(tw);
}

void SimpleTaskListWindow::deleteTask(simpleTaskListWidget* tw)
{
    SimpleTask *t = tw->task();

    QFile f(STGetTaskFileName(_stm->saveDir().c_str(), t));
    if(f.exists())
        f.remove();

    _stm->removeTask(t->id());

    ui->listTasks->takeItem(ui->listTasks->row(tw->myQLWI()));

    delete tw;
    delete t;
}

void SimpleTaskListWindow::setCurrent(int row)
{
    ui->listTasks->setCurrentRow(row);
}

void SimpleTaskListWindow::closeEvent(QCloseEvent *event)
{
    _stm->saveAll();
    event->accept();
}
