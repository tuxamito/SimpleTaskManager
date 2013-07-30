#include "simpletasklistwindow.h"
#include "ui_simpletasklistwindow.h"

#include <QListWidgetItem>
#include <QCloseEvent>
#include <QDirIterator>
#include <QFile>
#include <QDebug>

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
    vst_t tasks = _stm->currentTasks();

    for(auto i = tasks.begin(); i != tasks.end(); ++i)
    {
        SimpleTask *t = i->second;
        this->addTaskToList(t);
    }
}

void SimpleTaskListWindow::showOptions()
{

}

void SimpleTaskListWindow::addTask()
{
    emit newTask();
}

void SimpleTaskListWindow::addTaskToList(SimpleTask* task)
{
    QListWidgetItem *nw = new QListWidgetItem;
    simpleTaskListWidget *nt = new simpleTaskListWidget(nw);

    ui->listTasks->insertItem(ui->listTasks->count(), nw);
    ui->listTasks->setItemWidget(nw, nt);

    nw->setSizeHint(nt->sizeHint() + QSize(0, 20));

    nt->setTask(task);

    connect(nt, SIGNAL(showInfo(simpleTaskListWidget*)), this, SLOT(showInfo(simpleTaskListWidget*)));
    connect(nt, SIGNAL(deleteTask(simpleTaskListWidget*)), this, SLOT(deleteTask(simpleTaskListWidget*)));
    connect(nt, SIGNAL(showMenu(simpleTaskListWidget*)), this, SLOT(showMenu(simpleTaskListWidget*)));
}

void SimpleTaskListWindow::showMenu(simpleTaskListWidget *tw)
{
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

void SimpleTaskListWindow::closeEvent(QCloseEvent *event)
{
    _stm->saveAll();
    event->accept();
}
