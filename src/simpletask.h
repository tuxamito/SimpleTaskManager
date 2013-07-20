#ifndef SIMPLETASK_H
#define SIMPLETASK_H

#include <string>
#include <vector>
#include <ctime>
#include <cstdint>

enum STDoneType {NOTDONE, DONE};

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

    void setDescription(string description);
    string description();

    void setDone(STDoneType done);
    STDoneType done();

    void setTimeCreation(time_t timeCreation);
    time_t timeCreation();

    void setTimeDone(time_t timeDone);
    time_t timeDone();

private:
    uint32_t _id;
    string _name;

    STDoneType _done;

    string _description;

    time_t _timeCreation;
    time_t _timeDone;

    bool _modified;

    vector<class SimpleTask> _subTasks;

    inline void setModified();
};

#endif // SIMPLETASK_H
