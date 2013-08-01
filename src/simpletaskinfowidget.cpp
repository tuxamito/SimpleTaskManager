#include "simpletaskinfowidget.h"
#include "ui_simpletaskinfowidget.h"

#include <QString>
#include <ctime>

SimpleTaskInfoWidget::SimpleTaskInfoWidget(SimpleTask *st, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleTaskInfoWidget)
{
    ui->setupUi(this);

    _st = st;

    ui->labelHeading->setVisible(false);

#ifdef ANDROID
    int size = ui->checkDone->height() + 8;
    QString style("QCheckBox::indicator { width: " + QString::number(size) + "px; height: " + QString::number(size) + "px; }");
    ui->checkDone->setStyleSheet(style);
#endif

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

    if(ui->checkDone->isChecked())
    {
        _st->setDone(DONE);
    }
    else
    {
        _st->setDone(NOTDONE);
    }

    _st->setTimeCreation(ui->dateTimeCreation->dateTime().toTime_t());
    _st->setTimeDone(ui->dateTimeDone->dateTime().toTime_t());
    _st->setTimeDue(ui->dateTimeDue->dateTime().toTime_t());

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

    ui->checkDone->setChecked(_st->done() == DONE);
    this->changeTaskDone(ui->checkDone->isChecked());

    if(_st->timeCreation() == 0)
    {
        ui->dateTimeCreation->setDateTime(QDateTime::fromTime_t(time(NULL)));
    }
    else
    {
        ui->dateTimeCreation->setDateTime(QDateTime::fromTime_t(_st->timeCreation()));
    }

    ui->dateTimeDone->setDateTime(QDateTime::fromTime_t(_st->timeDone()));

    if(_st->timeDue() == 0)
    {
        ui->dateTimeDue->setDateTime(QDateTime::fromTime_t(time(NULL)));
    }
    else
    {
        ui->dateTimeDue->setDateTime(QDateTime::fromTime_t(_st->timeDue()));
    }
}

void SimpleTaskInfoWidget::changeTaskDone(bool done)
{
    if(done)
    {
        ui->checkDone->setText(tr("Yes!"));
    }
    else
    {
        ui->checkDone->setText(tr("No!"));
    }

    ui->dateTimeDone->setEnabled(done);
}
