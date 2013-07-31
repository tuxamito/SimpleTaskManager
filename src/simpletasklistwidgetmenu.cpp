#include "simpletasklistwidgetmenu.h"
#include "ui_simpletasklistwidgetmenu.h"

SimpleTaskListWidgetMenu::SimpleTaskListWidgetMenu(simpleTaskListWidget *tlw, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleTaskListWidgetMenu)
{
    //Set variables
    _tlw = tlw;

    ui->setupUi(this);
    this->installEventFilter(this);

#ifdef ANDROID
    ui->spacer1->changeSize(5, 10);
    ui->spacer2->changeSize(5, 10);
#else
    ui->spacer1->changeSize(5, 4);
    ui->spacer2->changeSize(5, 4);
#endif
}

SimpleTaskListWidgetMenu::~SimpleTaskListWidgetMenu()
{
    delete ui;
}

bool SimpleTaskListWidgetMenu::eventFilter(QObject *obj, QEvent *event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        this->close();
    }

    return QWidget::eventFilter(obj, event);
}

void SimpleTaskListWidgetMenu::showInfo()
{
    this->close();
    emit showTaskInfo(_tlw);
}

void SimpleTaskListWidgetMenu::addTask()
{
    this->close();
    emit showTaskAdd(_tlw);
}

void SimpleTaskListWidgetMenu::deleteTask()
{
    this->close();
    _tlw->deleteTask();
}
