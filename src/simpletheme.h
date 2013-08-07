#ifndef SIMPLETHEME_H
#define SIMPLETHEME_H

#include "simpletaskcommon.h"

class SimpleTheme
{
public:
    SimpleTheme();
    ~SimpleTheme();

    void setId(uint32_t id);
    uint32_t id();

    void setName(string name);
    string name();

    void setDescription(string description);
    string description();

private:
    uint32_t _id;
    string _name;
    string _description;
};

#endif // SIMPLETHEME_H
