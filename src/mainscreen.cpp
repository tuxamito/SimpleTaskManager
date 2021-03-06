#include "mainscreen.h"
#include "ui_mainscreen.h"

#include <QDir>
#include <QDirIterator>
#include <QDebug>

#define DATADIR "DATA"

mainScreen::mainScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainScreen)
{
    ui->setupUi(this);

    //Set variables
    _staw = NULL;
    _stsw = NULL;
    _stiw = NULL;
    _stmw = NULL;
    _blur = new QGraphicsBlurEffect(this);
    _blur->setEnabled(false);
    _showTaskInfo = NULL;
    _showAddSubTask = NULL;

#ifdef ANDROID
    _blur->setBlurRadius(5);
#else
    _blur->setBlurRadius(2);
#endif

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
    connect(_stlw, SIGNAL(showTaskInfo(simpleTaskListWidget*)), this, SLOT(showTaskInfo(simpleTaskListWidget*)));
    connect(_stlw, SIGNAL(showTaskMenu(simpleTaskListWidget*)), this, SLOT(showTaskListMenu(simpleTaskListWidget*)));

    //Show the default Window
    this->showTaskList();

    _stlw->setGraphicsEffect(_blur);
}

mainScreen::~mainScreen()
{
    delete ui;
    delete _blur;
    delete _stm;
}

void mainScreen::loadInitData()
{
    _stm->loadInitData();
}

void mainScreen::showAddTask()
{
    SimpleTask *st = new SimpleTask;
    SimpleTaskAddWindow *nt = new SimpleTaskAddWindow(st);

    nt->setAttribute(Qt::WA_DeleteOnClose);
    connect(nt, SIGNAL(newTask(SimpleTask*)), this, SLOT(createTask(SimpleTask*)));
    connect(nt, SIGNAL(destroyed()), this, SLOT(showTaskList()));

    ui->layout->removeWidget(_stlw);
    _stlw->setHidden(true);
    ui->layout->addWidget(nt);
    _staw = nt;
}

//WORK HERE!
void mainScreen::showAddSubTaskToTask(simpleTaskListWidget* tw)
{
    SimpleTaskAddSubTaskWindow *nt = new SimpleTaskAddSubTaskWindow(tw);

    nt->setAttribute(Qt::WA_DeleteOnClose);
    connect(nt, SIGNAL(newSubTask(simpleTaskListWidget*)), this, SLOT(createSubTask(simpleTaskListWidget*)));
    connect(nt, SIGNAL(destroyed()), this, SLOT(showTaskList()));

    ui->layout->removeWidget(_stlw);
    _stlw->setHidden(true);
    ui->layout->addWidget(nt);
    _stsw = nt;
}

void mainScreen::showTaskInfo(simpleTaskListWidget* tw)
{
    SimpleTaskInfoWindow *ti = new SimpleTaskInfoWindow(tw);
    ti->setAttribute(Qt::WA_DeleteOnClose);

    //connect(nt, SIGNAL(newTask(QString)), this, SLOT(createTask(QString)));
    connect(ti, SIGNAL(destroyed()), this, SLOT(showTaskList()));

    ui->layout->removeWidget(_stlw);
    _stlw->setHidden(true);
    ui->layout->addWidget(ti);
    _stiw = ti;
}

void mainScreen::showTaskInfoMenu(simpleTaskListWidget *tw)
{
    _showTaskInfo = tw;
}

void mainScreen::showAddSubTask(simpleTaskListWidget *tw)
{
    _showAddSubTask = tw;
}

void mainScreen::showTaskListMenu(simpleTaskListWidget *tlw)
{
    SimpleTaskListWidgetMenu *tm = new SimpleTaskListWidgetMenu(tlw);
    tm->setAttribute(Qt::WA_DeleteOnClose);

    //connect(nt, SIGNAL(newTask(QString)), this, SLOT(createTask(QString)));
    connect(tm, SIGNAL(destroyed()), this, SLOT(showTaskList()));
    connect(tm, SIGNAL(showTaskInfo(simpleTaskListWidget*)), this, SLOT(showTaskInfoMenu(simpleTaskListWidget*)));
    connect(tm, SIGNAL(showTaskAdd(simpleTaskListWidget*)), this, SLOT(showAddSubTask(simpleTaskListWidget*)));

    ui->layout->removeWidget(_stlw);
    _stlw->setHidden(false);

    _blur->setEnabled(true);

    ui->layout->addWidget(tm);
    _stmw = tm;
}

void mainScreen::showTaskList()
{
    if(_staw)
    {
        ui->layout->removeWidget(_staw);
        _staw = NULL;
    }
    else if(_stsw)
    {
        ui->layout->removeWidget(_stsw);
        _stsw = NULL;
    }
    else if(_stiw)
    {
        ui->layout->removeWidget(_stiw);
        _stiw = NULL;
    }
    else if(_stmw)
    {
        ui->layout->removeWidget(_stmw);
        _stlw->setCurrent(-1);
        _blur->setEnabled(false);
        _stmw = NULL;
    }

    ui->layout->addWidget(_stlw);
    _stlw->setHidden(false);

    if(_showTaskInfo)
    {
        this->showTaskInfo(_showTaskInfo);
        _showTaskInfo = NULL;
    }
    if(_showAddSubTask)
    {
        this->showAddSubTaskToTask(_showAddSubTask);
        _showAddSubTask = NULL;
    }
}

void mainScreen::createTask(SimpleTask *st)
{
    _stm->addTask(st);
    st->setModified();
    _stlw->update();
}

void mainScreen::createSubTask(simpleTaskListWidget*)
{
    _stlw->update();
}
