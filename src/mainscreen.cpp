#include "mainscreen.h"
#include "ui_mainscreen.h"

#include "simpletaskoperations.h"

#include <QDir>
#include <QDirIterator>

#define DATADIR "DATA"

mainScreen::mainScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainScreen)
{
    ui->setupUi(this);

    //Set variables
    _staw = NULL;

    //Create directory where data is stored if
    //it doesn't exist
    if(!QDir(DATADIR).exists())
        QDir().mkdir(DATADIR);

    //Create a task Manager & load Data
    _stm = new SimpleTaskManager();
    _stm->setSaveDir(DATADIR);
    this->loadInitData();

    //Create the Permanent Windows
    _stlw = new SimpleTaskListWindow(_stm, this);

    connect(_stlw, SIGNAL(newTask()), this, SLOT(showAddTask()));

    //Show the default Window
    this->showTaskList();
}

mainScreen::~mainScreen()
{
    delete ui;
    delete _stm;
}

void mainScreen::loadInitData()
{
    QDirIterator *dirIt;
    dirIt = new QDirIterator(_stm->saveDir().c_str(), QDirIterator::NoIteratorFlags);

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
            _stm->addTask(st);
        }
    }
}

void mainScreen::showAddTask()
{
    SimpleTaskAddWindow *nt = new SimpleTaskAddWindow();

    nt->setAttribute(Qt::WA_DeleteOnClose);
    connect(nt, SIGNAL(newTask(QString)), this, SLOT(createTask(QString)));
    connect(nt, SIGNAL(destroyed()), this, SLOT(showTaskList()));

    ui->layout->removeWidget(_stlw);
    _stlw->setHidden(true);
    ui->layout->addWidget(nt);
    _staw = nt;
}

void mainScreen::showTaskList()
{
    if(_staw)
    {
        ui->layout->removeWidget(_staw);
        _staw = NULL;
    }

    ui->layout->addWidget(_stlw);
    _stlw->setHidden(false);
}

void mainScreen::createTask(QString name)
{
    SimpleTask *st = new SimpleTask;
    st->setName(name.toUtf8().constData());

    _stm->addTask(st);
    st->setModified();
    _stlw->addTaskToList(st);
}
