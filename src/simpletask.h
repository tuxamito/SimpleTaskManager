#ifndef SIMPLETASK_H
#define SIMPLETASK_H

#include <string>
#include <vector>
#include <ctime>
#include <cstdint>

enum STDoneType {NOTDONE, DONE};
class SimpleTaskManager;

using namespace std;

class SimpleTask
{
public:
    SimpleTask();
    ~SimpleTask();

    bool isValid();

    void setId(uint32_t id);
    uint32_t id();

    void setName(string name);
    string name();
    string oldName();

    void setDescription(string description);
    string description();

    void setDone(STDoneType done);
    STDoneType done();

    void setTimeCreation(time_t timeCreation);
    time_t timeCreation();

    void setTimeDone(time_t timeDone);
    time_t timeDone();

    void setTimeDue(time_t timeDue);
    time_t timeDue();

    void setPriority(int priority);
    int priority();

    void setFather(SimpleTask *father);
    SimpleTask *father();

    void setManager(SimpleTaskManager *);
    SimpleTaskManager *manager();

    void setModified();
    bool modified();
    void setSaved();

private:
    uint32_t _id;
    string _name;
    string _oldName;

    STDoneType _done;

    string _description;

    time_t _timeCreation;
    time_t _timeDone;
    time_t _timeDue;

    int _priority;

    bool _modified;
    SimpleTask *_father;
    SimpleTaskManager *_manager;

    vector<class SimpleTask*> _subTasks;
};

#endif // SIMPLETASK_H
