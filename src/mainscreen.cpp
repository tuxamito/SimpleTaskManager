#include "mainscreen.h"
#include "ui_mainscreen.h"

#include <QListWidgetItem>

mainScreen::mainScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainScreen)
{
    ui->setupUi(this);

    QListWidgetItem *nw = new QListWidgetItem;
    simpleTaskListWidget *nt = new simpleTaskListWidget;

    ui->listTasks->insertItem(0, nw);
    ui->listTasks->setItemWidget(nw, nt);


    simpleTask *aaa = new simpleTask;

    aaa->setName("MyName");


    nt->setTask(aaa);
}

mainScreen::~mainScreen()
{
    delete ui;
}

void mainScreen::showOptions()
{

}

void mainScreen::addTask()
{

}
