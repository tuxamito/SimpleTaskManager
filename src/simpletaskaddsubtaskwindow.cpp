#include "simpletaskaddsubtaskwindow.h"
#include "ui_simpletaskaddsubtaskwindow.h"

SimpleTaskAddSubTaskWindow::SimpleTaskAddSubTaskWindow(simpleTaskListWidget *tw, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleTaskAddSubTaskWindow)
{
    ui->setupUi(this);
    _tw = tw;

    _st = new SimpleTask();

    _iw = new SimpleTaskInfoWidget(_st, this);
    _iw->setHeading(tr("Add New SubTask"));
    connect(_iw, SIGNAL(closeInfoAccept()), this, SLOT(acceptTask()));
    connect(_iw, SIGNAL(closeInfo()), this, SLOT(notAcceptTask()));

    ui->layout->addWidget(_iw);
}

SimpleTaskAddSubTaskWindow::~SimpleTaskAddSubTaskWindow()
{
    delete ui;
    delete _iw;
}

void SimpleTaskAddSubTaskWindow::acceptTask()
{
    emit newSubTask(_tw);
    _tw->task()->addSubTask(_st);
    this->close();
}

void SimpleTaskAddSubTaskWindow::notAcceptTask()
{
    delete _st;
    this->close();
}
