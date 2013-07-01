#include "mainscreen.h"
#include "ui_mainscreen.h"

#include <QListWidgetItem>

mainScreen::mainScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainScreen)
{
    ui->setupUi(this);

    QListWidgetItem *nw = new QListWidgetItem;
    //nw->setText("aaa");
    simpleTaskListWidget *nt = new simpleTaskListWidget;


    ui->listTasks->insertItem(1, nw);
    ui->listTasks->setItemWidget(nw, nt);
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
