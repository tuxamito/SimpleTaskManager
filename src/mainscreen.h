#ifndef MAINSCREEN_H
#define MAINSCREEN_H

#include <QWidget>

namespace Ui {
class mainScreen;
}

class mainScreen : public QWidget
{
    Q_OBJECT
    
public:
    explicit mainScreen(QWidget *parent = 0);
    ~mainScreen();

private:
    Ui::mainScreen *ui;
};

#endif // MAINSCREEN_H
