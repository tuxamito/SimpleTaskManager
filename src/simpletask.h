#ifndef SIMPLETASK_H
#define SIMPLETASK_H

#include <string>
#include <vector>

using namespace std;

class simpleTask
{
public:
    simpleTask();
    ~simpleTask();

    bool isValid();

    void setId(unsigned int id);
    unsigned int id();

    void setName(string name);
    string name();

private:
    unsigned int _id;
    string _name;
    //_dateCreation;
    //_dateModify;

    vector<class simpleTask> _subTasks;
};

#endif // SIMPLETASK_H
