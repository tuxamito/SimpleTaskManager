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
