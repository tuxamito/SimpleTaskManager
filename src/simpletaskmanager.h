#ifndef SIMPLETASKMANAGER_H
#define SIMPLETASKMANAGER_H

#include <unordered_set>
#include <unordered_map>
#include <list>

#include <QString>

#include "simpletaskcommon.h"
#include "simpletask.h"

class SimpleTaskManager
{
public:
    SimpleTaskManager();
    ~SimpleTaskManager();

    uint32_t addTask(SimpleTask *task);
    SimpleTask *task(uint32_t id);
    void removeTask(uint32_t id);
    void saveAll();

    void saveTask(SimpleTask *task);
    void setSaveDir(string dir);
    string saveDir();

    vst_t currentTasks();
    uint32_t getFreeId();
    void freeId(uint32_t id);

    lst_t getTaskList();

    void loadInitData(QString dir);
    void loadInitData();

private:
    vst_t _vst;
    unordered_set<uint32_t> _vui;

    string _dir;

    bool findId(uint32_t id);
};

#endif // SIMPLETASKMANAGER_H
