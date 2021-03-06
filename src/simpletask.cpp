#include "simpletask.h"
#include "simpletaskmanager.h"

#include <QByteArray>
#include <QFile>

SimpleTask::SimpleTask()
{
    _id = 0;
    _name = "";
    _oldName = "";
    _done = NOTDONE;
    _father = NULL;
    _manager = NULL;
    _modified = false;
    _timeCreation = 0;
    _timeDone = 0;
    _timeStart = 0;
    _timeDue = 0;
    _priority = 0;
    _level = 0;

    _expanded = true;

    _subTasks.clear();
}

SimpleTask::~SimpleTask()
{
}

void SimpleTask::setModified()
{
    _modified = true;
    if(_father)
    {
        _father->setModified();
    }
    else if (_manager)
    {
        _manager->saveTask(this);
    }
}

void SimpleTask::setSaved()
{
    _modified = false;
    _oldName = "";

    for(auto i = _subTasks.begin(); i != _subTasks.end(); ++i)
    {
        (*i).second->setSaved();
    }
}

bool SimpleTask::isValid()
{
    return _id != 0;
}

void SimpleTask::setId(uint32_t id)
{
    _id = id;
    this->setModified();
}

uint32_t SimpleTask::id()
{
    return _id;
}

void SimpleTask::setName(string name)
{
    _name = name;

    if(_oldName == "")
        _oldName = _name;

    this->setModified();
}

string SimpleTask::name()
{
    return _name;
}

string SimpleTask::oldName()
{
    return _oldName;
}

void SimpleTask::setDescription(string description)
{
    _description = description;
    this->setModified();
}

string SimpleTask::description()
{
    return _description;
}

void SimpleTask::setDone(STDoneType done)
{
    _done = done;
    this->setModified();
}

STDoneType SimpleTask::done()
{
    return _done;
}

void SimpleTask::setTimeCreation(time_t timeCreation)
{
    _timeCreation = timeCreation;
    this->setModified();
}

time_t SimpleTask::timeCreation()
{
    return _timeCreation;
}

void SimpleTask::setTimeDone(time_t timeDone)
{
    _timeDone = timeDone;
    this->setModified();
}

time_t SimpleTask::timeDone()
{
    return _timeDone;
}

void SimpleTask::setTimeStart(time_t timeStart)
{
    _timeDone = timeStart;
    this->setModified();
}

time_t SimpleTask::timeStart()
{
    return _timeStart;
}

void SimpleTask::setTimeDue(time_t timeDue)
{
    _timeDone = timeDue;
    this->setModified();
}

time_t SimpleTask::timeDue()
{
    return _timeDue;
}

unsigned int SimpleTask::level()
{
    return _level;
}

void SimpleTask::setLevel(unsigned int level)
{
    _level = level;
}

void SimpleTask::setPriority(int priority)
{
    _priority = priority;
    this->setModified();
}

int SimpleTask::priority()
{
    return _priority;
}

void SimpleTask::updateLevel()
{
    _level = _father->level() +1;
}

void SimpleTask::setFather(SimpleTask *father)
{
    _father = father;
    updateLevel();

    for(auto i = _subTasks.begin(); i != _subTasks.end(); ++i)
    {
        SimpleTask *t = i->second;
        t->updateLevel();
    }

    this->setModified();
}

SimpleTask *SimpleTask::father()
{
    return _father;
}

void SimpleTask::setManager(SimpleTaskManager *manager)
{
    _manager = manager;
}

SimpleTaskManager *SimpleTask::manager()
{
    return _manager;
}

void SimpleTask::setExpanded(bool expanded)
{
    _expanded = expanded;
}

bool SimpleTask::expanded()
{
    return _expanded;
}


uint32_t SimpleTask::getFreeId(uint32_t id)
{
    if(_manager)
    {
        return _manager->getFreeIdAndReserve(id);
    }
    else if(_father)
    {
        return _father->getFreeId(id);
    }
    else
    {
        return 0;
    }
}

void SimpleTask::freeId(uint32_t id)
{
    if(_manager)
    {
        _manager->freeId(id);
    }
    else if(_father)
    {
        _father->freeId(id);
    }
}

void SimpleTask::addSubTask(SimpleTask *task)
{
    task->setFather(this);
    task->setId(this->getFreeId(task->id()));
    this->_subTasks.insert(vst_t::value_type(task->id(), task));
    this->setModified();
}

void SimpleTask::removeSubTask(uint32_t id)
{
    auto elem = _subTasks.find(id);
    if(elem != _subTasks.end())
    {
        _subTasks.erase(elem);
        this->freeId(id);
    }
}

bool SimpleTask::modified()
{
    return _modified;
}

vst_t* SimpleTask::getSubTasks()
{
    return &_subTasks;
}

lst_t SimpleTask::getSubTaskList()
{
    lst_t list;

    for(auto i = _subTasks.begin(); i != _subTasks.end(); ++i)
    {
        SimpleTask *t = i->second;
        list.push_back(t);

        if(t->expanded())
        {
            lst_t _list = t->getSubTaskList();
            list.splice(list.end(), _list);
        }
    }

    return list;
}

void SimpleTask::subTasksFigures(int *number, int *done)
{
    int _n = 0;
    int _d = 0;

    int _nS = 0;
    int _nD = 0;

    _n += _subTasks.size();

    for(auto i = _subTasks.begin(); i != _subTasks.end(); ++i)
    {
        SimpleTask *t = i->second;
        if(t->done())
            ++_d;
        t->subTasksFigures(&_nS, &_nD);
        _n += _nS;
        _d += _nD;
    }

    *number = _n;
    *done = _d;
}
