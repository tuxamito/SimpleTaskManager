#include "addtaskdialog.h"
#include "ui_addtaskdialog.h"

addTaskDialog::addTaskDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addTaskDialog)
{
    ui->setupUi(this);

    connect(this, SIGNAL(accepted()), this, SLOT(acceptWork()));
}

addTaskDialog::~addTaskDialog()
{
    delete ui;
}

void addTaskDialog::acceptWork()
{
    emit newTask(ui->lineTaskName->text());
}
