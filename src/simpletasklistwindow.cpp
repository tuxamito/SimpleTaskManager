#include "simpletasklistwindow.h"
#include "ui_simpletasklistwindow.h"

#include <QListWidgetItem>
#include <QCloseEvent>
#include <QDirIterator>
#include <QFile>
#include <QDebug>

#include "simpletaskaddwindow.h"

#include "addtaskdialog.h"
#include "simpletaskoperations.h"

#define DATADIR "DATA"

SimpleTaskListWindow::SimpleTaskListWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleTaskListWindow)
{
    ui->setupUi(this);

    if(!QDir(DATADIR).exists())
        QDir().mkdir(DATADIR);

    _stm.setSaveDir(DATADIR);
    this->loadInitData();
}

SimpleTaskListWindow::~SimpleTaskListWindow()
{
    delete ui;
}

void SimpleTaskListWindow::loadInitData()
{
    QDirIterator *dirIt;
    dirIt = new QDirIterator(DATADIR, QDirIterator::NoIteratorFlags);

    while (dirIt->hasNext())
    {
        dirIt->next();
        QString _f = dirIt->filePath();
        QFileInfo f(_f);

        if(f.suffix() == "stb")
        {
            QFile dfile(dirIt->filePath());

            dfile.open(QIODevice::ReadOnly);

            SimpleTask *st = STFromBinary(dfile.readAll());

            _stm.addTask(st);

            this->addTaskToList(st);
        }
    }
}

void SimpleTaskListWindow::showOptions()
{

}

void SimpleTaskListWindow::addTask()
{
    SimpleTaskAddWindow *nt = new SimpleTaskAddWindow();

    connect(nt, SIGNAL(newTask(QString)), this, SLOT(createTask(QString)));
    connect(nt, SIGNAL(destroyed()), this, SLOT(repaint()));

#ifdef ANDROID
    nt->showFullScreen();
#else
    nt->show();
#endif
}

void SimpleTaskListWindow::createTask(QString name)
{
    SimpleTask *st = new SimpleTask;
    st->setName(name.toUtf8().constData());

    _stm.addTask(st);
    st->setModified();
    this->addTaskToList(st);
}

void SimpleTaskListWindow::addTaskToList(SimpleTask* task)
{
    QListWidgetItem *nw = new QListWidgetItem;
    simpleTaskListWidget *nt = new simpleTaskListWidget(nw);

    ui->listTasks->insertItem(ui->listTasks->count(), nw);
    ui->listTasks->setItemWidget(nw, nt);

    nt->setTask(task);

    connect(nt, SIGNAL(deleteTask(simpleTaskListWidget*)), this, SLOT(deleteTask(simpleTaskListWidget*)));
}

void SimpleTaskListWindow::deleteTask(simpleTaskListWidget* tw)
{
    SimpleTask *t = tw->task();

    QFile f(STGetTaskFileName(DATADIR, t));
    if(f.exists())
        f.remove();

    _stm.removeTask(t->id());

    ui->listTasks->takeItem(ui->listTasks->row(tw->myQLWI()));

    delete tw;
    delete t;
}

void SimpleTaskListWindow::closeEvent(QCloseEvent *event)
{
    _stm.saveAll();
    event->accept();
}
