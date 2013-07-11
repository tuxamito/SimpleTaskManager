#include "simpletask.h"
#include "simpletaskoperations.h"

#include <QByteArray>
#include <QFile>

SimpleTask::SimpleTask()
{
    _id = 0;
    _name = "";
    _done = NOTDONE;
}

SimpleTask::~SimpleTask()
{
}

bool SimpleTask::isValid()
{
    return _id != 0;
}

void SimpleTask::setId(uint32_t id)
{
    _id = id;
}

uint32_t SimpleTask::id()
{
    return _id;
}

void SimpleTask::setName(string name)
{
    _name = name;
}

string SimpleTask::name()
{
    return _name;
}

void SimpleTask::setDescription(string description)
{
    _description = description;
}

string SimpleTask::description()
{
    return _description;
}

void SimpleTask::setDone(STDoneType done)
{
    _done = done;

    STSaveToFile(".", this);
}

STDoneType SimpleTask::done()
{
    return _done;
}

void SimpleTask::setTimeCreation(time_t timeCreation)
{
    _timeCreation = timeCreation;
}

time_t SimpleTask::timeCreation()
{
    return _timeCreation;
}

void SimpleTask::setTimeDone(time_t timeDone)
{
    _timeDone = timeDone;
}

time_t SimpleTask::timeDone()
{
    return _timeDone;
}
