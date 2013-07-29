#include "simpletaskaddwindow.h"
#include "ui_simpletaskaddwindow.h"

SimpleTaskAddWindow::SimpleTaskAddWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleTaskAddWindow)
{
    ui->setupUi(this);

#ifdef ANDROID
    this->setWindowOpacity(0.2);
    ui->lineTaskName->setMinimumHeight(ui->lineTaskName->height() + 4);
    //this->setMinimumHeight(this->height() + 10);

    this->repaint();
#else
    this->setWindowOpacity(1.0);
#endif
}

SimpleTaskAddWindow::~SimpleTaskAddWindow()
{
    delete ui;
}

void SimpleTaskAddWindow::acceptTask()
{
    emit newTask(ui->lineTaskName->text());

    this->close();
}
