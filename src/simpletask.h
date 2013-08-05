#ifndef SIMPLETASK_H
#define SIMPLETASK_H

#include <string>
#include <ctime>

#include "simpletaskcommon.h"

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

    void setManager(SimpleTaskManager *manager);
    SimpleTaskManager *manager();

    void addSubTask(SimpleTask *task);
    void removeSubTask(uint32_t id);

    uint32_t getFreeId(uint32_t id);
    void freeId(uint32_t id);

    vst_t* getSubTasks();

    void setModified();
    bool modified();
    void setSaved();

    void updateLevel();
    unsigned int level();
    void setLevel(unsigned int level);

    lst_t getSubTaskList();

    void subTasksFigures(int *number, int *done);

    void setExpanded(bool extended);
    bool expanded();

    friend class SimpleTaskManager;

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
    unsigned int _level;

    bool _modified;
    SimpleTask *_father;
    SimpleTaskManager *_manager;

    bool _expanded;

    vst_t _subTasks;
};

#endif // SIMPLETASK_H
