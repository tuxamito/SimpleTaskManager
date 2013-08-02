#include "simpletaskaddwindow.h"
#include "ui_simpletaskaddwindow.h"

SimpleTaskAddWindow::SimpleTaskAddWindow(SimpleTask *st, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleTaskAddWindow)
{
    ui->setupUi(this);
    _st = st;

    _iw = new SimpleTaskInfoWidget(_st, this);
    _iw->setHeading(tr("Add New Task"));
    connect(_iw, SIGNAL(closeInfoAccept()), this, SLOT(acceptTask()));
    connect(_iw, SIGNAL(closeInfo()), this, SLOT(notAcceptTask()));

    ui->layout->addWidget(_iw);
}

SimpleTaskAddWindow::~SimpleTaskAddWindow()
{
    delete ui;
    delete _iw;
}

void SimpleTaskAddWindow::acceptTask()
{
    emit newTask(_st);
    this->close();
}

void SimpleTaskAddWindow::notAcceptTask()
{
    delete _st;
    this->close();
}
