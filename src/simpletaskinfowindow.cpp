#include "simpletaskinfowindow.h"
#include "ui_simpletaskinfowindow.h"

SimpleTaskInfoWindow::SimpleTaskInfoWindow(simpleTaskListWidget *tw, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleTaskInfoWindow)
{
    _tw = tw;

    ui->setupUi(this);

    loadInfo();
}

SimpleTaskInfoWindow::~SimpleTaskInfoWindow()
{
    delete ui;
}

void SimpleTaskInfoWindow::accept()
{
    _tw->task()->setName(ui->lineName->text().toUtf8().constData());
    _tw->redraw();

    this->close();
}

void SimpleTaskInfoWindow::loadInfo()
{
    ui->lineName->setText(QString::fromUtf8(_tw->task()->name().c_str()));
}
