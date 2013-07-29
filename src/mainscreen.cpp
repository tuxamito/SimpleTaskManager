#include "mainscreen.h"
#include "ui_mainscreen.h"

#include <QDir>

#define DATADIR "DATA"

mainScreen::mainScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainScreen)
{
    ui->setupUi(this);

    //Create directory where data is stored if
    //it doesn't exist
    if(!QDir(DATADIR).exists())
        QDir().mkdir(DATADIR);

    //Create a task Manager
    _stm = new SimpleTaskManager();
    _stm->setSaveDir(DATADIR);

    //Create the Permanent Windows
    _stlw = new SimpleTaskListWindow(_stm, this);

    //Show the default Window
    ui->layout->addWidget(_stlw);
}

mainScreen::~mainScreen()
{
    delete ui;
    delete _stm;
}
