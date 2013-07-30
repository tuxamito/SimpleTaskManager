#ifndef SIMPLETASKLISTWIDGETMENU_H
#define SIMPLETASKLISTWIDGETMENU_H

#include <QWidget>

namespace Ui {
class SimpleTaskListWidgetMenu;
}

class SimpleTaskListWidgetMenu : public QWidget
{
    Q_OBJECT
    
public:
    explicit SimpleTaskListWidgetMenu(QWidget *parent = 0);
    ~SimpleTaskListWidgetMenu();

protected:
    bool eventFilter(QObject *obj, QEvent *event);

private:
    Ui::SimpleTaskListWidgetMenu *ui;
};

#endif // SIMPLETASKLISTWIDGETMENU_H
