#ifndef SIMPLETASKLISTWINDOWDATA_H
#define SIMPLETASKLISTWINDOWDATA_H

#include <list>

#include "simpletasklistwidget.h"

class SimpleTaskListWindowData
{
public:
    SimpleTaskListWindowData(simpleTaskListWidget *w=NULL);
    ~SimpleTaskListWindowData();

    static std::list<simpleTaskListWidget*> taskToShow(SimpleTaskListWindowData *data);

    void addTask(simpleTaskListWidget *task);

    simpleTaskListWidget *getWidget();
    std::list<SimpleTaskListWindowData> getList();

private:
    std::list<SimpleTaskListWindowData> _data;
    simpleTaskListWidget *_w;
};

#endif // SIMPLETASKLISTWINDOWDATA_H
