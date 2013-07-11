#include "mainscreen.h"
#include "ui_mainscreen.h"

#include <QListWidgetItem>
#include <QCloseEvent>
#include <QDirIterator>
#include <QFile>
#include <QDebug>

#include "addtaskdialog.h"
#include "simpletaskoperations.h"

mainScreen::mainScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainScreen)
{
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
    dirIt = new QDirIterator(".", QDirIterator::NoIteratorFlags);

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

    this->addTaskToList(st);

    STSaveToFile(".", st);
}

void mainScreen::addTaskToList(SimpleTask* task)
{
    QListWidgetItem *nw = new QListWidgetItem;
    simpleTaskListWidget *nt = new simpleTaskListWidget;

    ui->listTasks->insertItem(ui->listTasks->count(), nw);
    ui->listTasks->setItemWidget(nw, nt);

    nt->setTask(task);
}

void mainScreen::closeEvent(QCloseEvent *event)
{
    //event->ignore();
    event->accept();
}
