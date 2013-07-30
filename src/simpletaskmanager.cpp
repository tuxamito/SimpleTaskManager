#include "simpletaskmanager.h"
#include "simpletaskoperations.h"

#include <algorithm>

SimpleTaskManager::SimpleTaskManager()
{
    _dir = "";
}

SimpleTaskManager::~SimpleTaskManager()
{
}

void SimpleTaskManager::setSaveDir(string dir)
{
    _dir = dir;
}

string SimpleTaskManager::saveDir()
{
    return _dir;
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
            task->setManager(this);
        }
    }

    if(!nid)
    {
        nid = this->getFreeId();
        if(nid)
        {
            task->setId(nid);
            _vui.insert(nid);
            _vst.insert(vst_t::value_type(nid, task));
            task->setManager(this);
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
        _vui.erase(id);
    }
}

void SimpleTaskManager::saveAll()
{
    for(auto i = _vst.begin(); i != _vst.end(); ++i)
    {
        SimpleTask *t = i->second;
        if(t->modified())
        {
            STSaveToFile(_dir, t);
            t->setSaved();
        }
    }
}

vst_t SimpleTaskManager::currentTasks()
{
    return _vst;
}

void SimpleTaskManager::saveTask(SimpleTask *task)
{
    STSaveToFile(_dir, task);
    task->setSaved();
}
