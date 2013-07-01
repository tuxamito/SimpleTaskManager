#ifndef SIMPLETASK_H
#define SIMPLETASK_H

#include <string>
#include <vector>
#include <ctime>

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

    void setTimeCreation(time_t timeCreation);
    time_t timeCreation();

    void setTimeDone(time_t timeDone);
    time_t timeDone();

private:
    unsigned int _id;
    string _name;

    bool _done;

    string _description;

    time_t _timeCreation;
    time_t _timeDone;

    vector<class simpleTask> _subTasks;
};

#endif // SIMPLETASK_H
