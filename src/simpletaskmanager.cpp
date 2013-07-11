#include "simpletaskmanager.h"

#include <algorithm>

SimpleTaskManager::SimpleTaskManager()
{
}

SimpleTaskManager::~SimpleTaskManager()
{
}

bool SimpleTaskManager::findId(uint32_t id)
{
    return _vui.find(id) != _vui.end();
}

uint32_t SimpleTaskManager::getFreeId()
{
    for(uint32_t i = 1; i!=0; i++)
    {
        if(_vui.find(i) == _vui.end())
            return i;
    }

    return 0;
}

uint32_t SimpleTaskManager::addTask(SimpleTask *task)
{
    uint32_t nid = task->id();

    if(nid)
    {
        if(_vui.find(nid) != _vui.end())
        {
            nid = 0;
        }
        else
        {
            _vui.insert(nid);
            _vst.insert(vst_t::value_type(nid, task));
        }
    }
    else
    {
        nid = this->getFreeId();
        if(nid)
        {
            task->setId(nid);
            _vui.insert(nid);
            _vst.insert(vst_t::value_type(nid, task));
        }
    }

    return nid;
}

SimpleTask *SimpleTaskManager::task(uint32_t id)
{
    vst_t::iterator elem;

    elem = _vst.find(id);
    if(elem != _vst.end())
    {
        return (*elem).second;
    }

    return NULL;
}

void SimpleTaskManager::removeTask(uint32_t id)
{
    vst_t::iterator elem;

    elem = _vst.find(id);
    if(elem != _vst.end())
    {
        _vst.erase(elem);
    }
}
