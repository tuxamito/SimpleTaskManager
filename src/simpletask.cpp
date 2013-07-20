#include "simpletask.h"
#include "simpletaskoperations.h"

#include <QByteArray>
#include <QFile>

SimpleTask::SimpleTask()
{
    _id = 0;
    _name = "";
    _done = NOTDONE;

    _modified = false;
}

SimpleTask::~SimpleTask()
{
}

inline void SimpleTask::setModified()
{
    _modified = true;
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
    this->setModified();
}

string SimpleTask::name()
{
    return _name;
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
