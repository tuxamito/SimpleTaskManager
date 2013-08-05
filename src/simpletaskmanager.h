#ifndef SIMPLETASKMANAGER_H
#define SIMPLETASKMANAGER_H

#include <unordered_set>
#include <unordered_map>
#include <list>

#include <QString>
#include <QJsonObject>

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
    uint32_t getFreeIdAndReserve(uint32_t proposedID);
    uint32_t getFreeId();
    void freeId(uint32_t id);

    lst_t getTaskList();

    void loadInitData(QString dir);
    void loadInitData();

    //FROM OPERATIONS
    QString STGetTaskFileName(string dir, SimpleTask *task);

private:
    //FROM OPERATIONS
    QJsonObject STToJSON(SimpleTask *st);
    SimpleTask *STFromJSON(QJsonObject obj, SimpleTask *father=NULL);

    QString STToQString(SimpleTask *st);
    QByteArray STToBinary(SimpleTask *st);

    SimpleTask *STFromQString(QString st);
    SimpleTask *STFromBinary(QByteArray st);

    QString STGetTaskFileOldName(string dir, SimpleTask *task);
    void STSaveToFile(string dir, SimpleTask *task);

    int STDoneTypeToInt(STDoneType val);
    STDoneType IntToSTDoneType(int val);

    vst_t _vst;
    unordered_set<uint32_t> _vui;

    string _dir;

    bool findId(uint32_t id);
};

#endif // SIMPLETASKMANAGER_H
