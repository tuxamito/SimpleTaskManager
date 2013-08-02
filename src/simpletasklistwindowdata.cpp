#include "simpletasklistwindowdata.h"

SimpleTaskListWindowData::SimpleTaskListWindowData(simpleTaskListWidget *w)
{
    _w = w;
}

SimpleTaskListWindowData::~SimpleTaskListWindowData()
{

}

std::list<simpleTaskListWidget*> SimpleTaskListWindowData::taskToShow(SimpleTaskListWindowData *data)
{
    list<simpleTaskListWidget*> _list;
    std::list<SimpleTaskListWindowData> _data = data->getList();

    for(auto i = _data.begin(); i != _data.end(); ++i)
    {
        SimpleTaskListWindowData *d = &(*i);
        simpleTaskListWidget *w = d->getWidget();
        _list.push_back(w);

        if(w->expanded())
        {
            std::list<simpleTaskListWidget*> l = taskToShow(d);

            for(auto j = l.begin(); j != l.end(); ++j)
            {
                _list.push_back((*j));
            }
        }
    }

    return _list;
}

void SimpleTaskListWindowData::addTask(simpleTaskListWidget *task)
{
    SimpleTaskListWindowData nt(task);
    _data.push_back(nt);
}

simpleTaskListWidget *SimpleTaskListWindowData::getWidget()
{
    return _w;
}

std::list<SimpleTaskListWindowData> SimpleTaskListWindowData::getList()
{
    return _data;
}
