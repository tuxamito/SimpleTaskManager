#include "simpletheme.h"

SimpleTheme::SimpleTheme()
{
}

SimpleTheme::~SimpleTheme()
{
}

void SimpleTheme::setId(uint32_t id)
{
    _id = id;
}

uint32_t SimpleTheme::id()
{
    return _id;
}

void SimpleTheme::setName(string name)
{
    _name = name;
}

string SimpleTheme::name()
{
    return _name;
}

void SimpleTheme::setDescription(string description)
{
    _description = description;
}

string SimpleTheme::description()
{
    return _description;
}
