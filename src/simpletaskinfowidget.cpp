#include "simpletaskinfowidget.h"
#include "ui_simpletaskinfowidget.h"

SimpleTaskInfoWidget::SimpleTaskInfoWidget(SimpleTask *st, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleTaskInfoWidget)
{
    ui->setupUi(this);

    _st = st;

    ui->labelHeading->setVisible(false);
    loadInfo();
}

SimpleTaskInfoWidget::~SimpleTaskInfoWidget()
{
    delete ui;
}

void SimpleTaskInfoWidget::setHeading(QString heading)
{
    ui->labelHeading->setText(heading.trimmed());
    ui->labelHeading->setVisible(heading.trimmed() != "");
}

void SimpleTaskInfoWidget::accept()
{
    _st->setName(ui->lineName->text().toUtf8().constData());
    _st->setDescription(ui->lineDescription->text().toUtf8().constData());
    emit closeInfoAccept();
}

void SimpleTaskInfoWidget::cancel()
{
    emit closeInfo();
}

void SimpleTaskInfoWidget::loadInfo()
{
    ui->lineName->setText(QString::fromUtf8(_st->name().c_str()));
    ui->lineDescription->setText(QString::fromUtf8(_st->description().c_str()));
}
