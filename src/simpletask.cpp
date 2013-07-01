#include "simpletask.h"

simpleTask::simpleTask()
{
    _id = 0;
    _name = "";
}

simpleTask::~simpleTask()
{
}

bool simpleTask::isValid()
{
    return _id != 0;
}

void simpleTask::setId(unsigned int id)
{
    _id = id;
}

unsigned int simpleTask::id()
{
    return _id;
}

void simpleTask::setName(string name)
{
    _name = name;
}

string simpleTask::name()
{
    return _name;
}

void simpleTask::setDescription(string description)
{
    _description = description;
}

string simpleTask::description()
{
    return _description;
}

void simpleTask::setDone(bool done)
{
    _done = done;
}

bool simpleTask::done()
{
    return _done;
}

void simpleTask::setTimeCreation(time_t timeCreation)
{
    _timeCreation = timeCreation;
}

time_t simpleTask::timeCreation()
{
    return _timeCreation;
}

void simpleTask::setTimeDone(time_t timeDone)
{
    _timeDone = timeDone;
}

time_t simpleTask::timeDone()
{
    return _timeDone;
}
