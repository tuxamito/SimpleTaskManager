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

    //Show the default Window
    ui->layout->addWidget(_stlw);
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
