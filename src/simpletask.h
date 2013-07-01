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

    void setDescription(string description);
    string description();

    void setDone(bool done);
    bool done();

private:
    unsigned int _id;
    string _name;

    bool _done;

    string _description;

    //_dateCreation;
    //_dateModify;

    vector<class simpleTask> _subTasks;
};

#endif // SIMPLETASK_H
