#include "mainscreen.h"
#include "ui_mainscreen.h"

mainScreen::mainScreen(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainScreen)
{
    ui->setupUi(this);
}

mainScreen::~mainScreen()
{
    delete ui;
}
