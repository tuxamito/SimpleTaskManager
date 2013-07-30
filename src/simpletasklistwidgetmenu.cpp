#include "simpletasklistwidgetmenu.h"
#include "ui_simpletasklistwidgetmenu.h"

SimpleTaskListWidgetMenu::SimpleTaskListWidgetMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimpleTaskListWidgetMenu)
{
    ui->setupUi(this);
    this->installEventFilter(this);
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
