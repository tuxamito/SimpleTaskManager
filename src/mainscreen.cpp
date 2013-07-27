#include "mainscreen.h"
#include "ui_mainscreen.h"

#include <QListWidgetItem>
#include <QCloseEvent>
#include <QDirIterator>
#include <QFile>
#include <QDebug>

#include "addtaskdialog.h"
#include "simpletaskoperations.h"

#define DATADIR "DATA"

mainScreen::mainScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainScreen)
{
    if(!QDir(DATADIR).exists())
        QDir().mkdir(DATADIR);

    _stm.setSaveDir(DATADIR);

    ui->setupUi(this);

    this->loadInitData();
}

mainScreen::~mainScreen()
{
    delete ui;
}

void mainScreen::loadInitData()
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

void mainScreen::showOptions()
{

}

void mainScreen::addTask()
{
    addTaskDialog *nt = new addTaskDialog(this);
    connect(nt, SIGNAL(newTask(QString)), this, SLOT(createTask(QString)));

    nt->exec();

    this->repaint();
}

void mainScreen::createTask(QString name)
{
    SimpleTask *st = new SimpleTask;
    st->setName(name.toUtf8().constData());

    _stm.addTask(st);
    st->setModified();
    this->addTaskToList(st);
}

void mainScreen::addTaskToList(SimpleTask* task)
{
    QListWidgetItem *nw = new QListWidgetItem;
    simpleTaskListWidget *nt = new simpleTaskListWidget(nw);

    ui->listTasks->insertItem(ui->listTasks->count(), nw);
    ui->listTasks->setItemWidget(nw, nt);

    nt->setTask(task);

    connect(nt, SIGNAL(deleteTask(simpleTaskListWidget*)), this, SLOT(deleteTask(simpleTaskListWidget*)));
}

void mainScreen::deleteTask(simpleTaskListWidget* tw)
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

void mainScreen::closeEvent(QCloseEvent *event)
{
    _stm.saveAll();
    event->accept();
}
