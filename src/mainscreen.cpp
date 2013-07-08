#include "mainscreen.h"
#include "ui_mainscreen.h"

#include <QListWidgetItem>
#include <QCloseEvent>
#include <QDebug>

#include "addtaskdialog.h"

mainScreen::mainScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainScreen)
{
    ui->setupUi(this);
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
    addTaskDialog *nt = new addTaskDialog(this);
    connect(nt, SIGNAL(newTask(QString)), this, SLOT(createTask(QString)));
    nt->exec();
}

void mainScreen::createTask(QString name)
{
    SimpleTask *st = new SimpleTask;
    st->setName(name.toUtf8().constData());

    QListWidgetItem *nw = new QListWidgetItem;
    simpleTaskListWidget *nt = new simpleTaskListWidget;

    ui->listTasks->insertItem(ui->listTasks->count(), nw);
    ui->listTasks->setItemWidget(nw, nt);

    nt->setTask(st);
}

void mainScreen::closeEvent(QCloseEvent *event)
{
    event->ignore();
    //event->accept();
}
