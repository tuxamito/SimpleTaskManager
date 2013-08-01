#include "simpletaskinfowindow.h"
#include "ui_simpletaskinfowindow.h"

SimpleTaskInfoWindow::SimpleTaskInfoWindow(simpleTaskListWidget *tw, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleTaskInfoWindow)
{
    _tw = tw;
    ui->setupUi(this);

    _iw = new SimpleTaskInfoWidget(_tw->task(), this);
    _iw->setHeading(tr("Modify Task"));
    connect(_iw, SIGNAL(closeInfoAccept()), this, SLOT(accept()));
    connect(_iw, SIGNAL(closeInfo()), this, SLOT(accept()));

    ui->layout->addWidget(_iw);
}

SimpleTaskInfoWindow::~SimpleTaskInfoWindow()
{
    delete ui;
}

void SimpleTaskInfoWindow::accept()
{
    _tw->redraw();
    this->close();
}
