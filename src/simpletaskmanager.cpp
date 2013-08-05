#include "simpletaskmanager.h"

#include <algorithm>

#include <QDirIterator>
#include <QFile>
#include <QFileInfo>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

SimpleTaskManager::SimpleTaskManager()
{
    _dir = "";
}

SimpleTaskManager::~SimpleTaskManager()
{
}

void SimpleTaskManager::setSaveDir(string dir)
{
    _dir = dir;
}

string SimpleTaskManager::saveDir()
{
    return _dir;
}

void SimpleTaskManager::loadInitData(QString dir)
{
    QDirIterator *dirIt;
    dirIt = new QDirIterator(dir, QDirIterator::NoIteratorFlags);

    while (dirIt->hasNext())
    {
        dirIt->next();
        QString _f = dirIt->filePath();
        QFileInfo f(_f);

        if(f.suffix() == "stb")
        {
            QFile dfile(dirIt->filePath());
            dfile.open(QIODevice::ReadOnly);

            SimpleTask *st = STFromBinary(dfile.readAll());
            this->addTask(st);
        }
    }
}

void SimpleTaskManager::loadInitData()
{
    loadInitData(_dir.c_str());
}

bool SimpleTaskManager::findId(uint32_t id)
{
    return _vui.find(id) != _vui.end();
}

uint32_t SimpleTaskManager::getFreeIdAndReserve(uint32_t proposedID)
{
    uint32_t id;

    if(proposedID == 0)
    {
        id = this->getFreeId();
    }
    else
    {
        if(_vui.find(proposedID) != _vui.end())
        {
            id = this->getFreeId();
        }
        else
        {
            id = proposedID;
        }
    }

    _vui.insert(id);
    return id;
}

uint32_t SimpleTaskManager::getFreeId()
{
    for(uint32_t i = 1; i!=0; i++)
    {
        if(_vui.find(i) == _vui.end())
            return i;
    }

    return 0;
}

uint32_t SimpleTaskManager::addTask(SimpleTask *task)
{
    uint32_t nid = task->id();

    if(nid)
    {
        if(_vui.find(nid) != _vui.end())
        {
            nid = 0;
        }
        else
        {
            _vui.insert(nid);
            _vst.insert(vst_t::value_type(nid, task));
            task->setManager(this);
        }
    }

    if(!nid)
    {
        nid = this->getFreeId();
        if(nid)
        {
            task->setId(nid);
            _vui.insert(nid);
            _vst.insert(vst_t::value_type(nid, task));
            task->setManager(this);
        }
    }

    return nid;
}

SimpleTask *SimpleTaskManager::task(uint32_t id)
{
    vst_t::iterator elem;

    elem = _vst.find(id);
    if(elem != _vst.end())
    {
        return (*elem).second;
    }

    return NULL;
}

void SimpleTaskManager::removeTask(uint32_t id)
{
    vst_t::iterator elem;

    elem = _vst.find(id);
    if(elem != _vst.end())
    {
        _vst.erase(elem);
        _vui.erase(id);
    }
}

void SimpleTaskManager::saveAll()
{
    for(auto i = _vst.begin(); i != _vst.end(); ++i)
    {
        SimpleTask *t = i->second;
        if(t->modified())
        {
            this->saveTask(t);
        }
    }
}

void SimpleTaskManager::saveTask(SimpleTask *task)
{
    if(task->name() != "")
    {
        STSaveToFile(_dir, task);
        task->setSaved();
    }
}

vst_t SimpleTaskManager::currentTasks()
{
    return _vst;
}

void SimpleTaskManager::freeId(uint32_t id)
{
    _vui.erase(id);
}

lst_t SimpleTaskManager::getTaskList()
{
    lst_t list;

    for(auto i = _vst.begin(); i != _vst.end(); ++i)
    {
        SimpleTask *t = i->second;
        list.push_back(t);

        if(t->expanded())
        {
            lst_t _list = t->getSubTaskList();
            list.merge(_list);
        }
    }

    return list;
}

//FROM Operations

QJsonObject SimpleTaskManager::STToJSON(SimpleTask *st)
{
    QJsonObject obj;

    obj.insert("id", QJsonValue(QString::number(st->id())));
    obj.insert("name", QJsonValue(QString(st->name().c_str())));
    obj.insert("description", QJsonValue(QString(st->description().c_str())));
    obj.insert("done", QJsonValue(QString::number(STDoneTypeToInt(st->done()))));
    obj.insert("timeCreation", QJsonValue(QString::number(st->timeCreation())));
    obj.insert("timeDone", QJsonValue(QString::number(st->timeDone())));
    obj.insert("timeDue", QJsonValue(QString::number(st->timeDue())));
    obj.insert("priority", QJsonValue(QString::number(st->priority())));
    obj.insert("level", QJsonValue(QString::number(st->level())));

    return obj;
}

QString SimpleTaskManager::STToQString(SimpleTask *st)
{
    QJsonDocument doc;
    QJsonObject obj;
    QJsonArray subTasks;

    obj = STToJSON(st);

    //Add subtasks
    vst_t *sts = st->getSubTasks();
    for(auto i = sts->begin(); i != sts->end(); ++i)
    {
        SimpleTask *sub = i->second;
        QJsonObject obj2 = STToJSON(sub);
        subTasks.append(QJsonValue(obj2));
    }

    obj.insert("subTasks", QJsonValue(subTasks));

    doc.setObject(obj);

    return QString(doc.toJson());
}

QByteArray SimpleTaskManager::STToBinary(SimpleTask *st)
{
#ifdef COMPRESS
    return qCompress(STToQString(st).toUtf8());
#else
    return STToQString(st).toUtf8();
#endif
}

SimpleTask *SimpleTaskManager::STFromJSON(QJsonObject obj, SimpleTask *father)
{
    SimpleTask *_st;
    _st = new SimpleTask;

    if(father != NULL)
    {
        _st->_father = father;
    }
    else
    {
        _st->_manager = this;
    }

    _st->_name = obj.value("name").toString().toUtf8().constData();
    _st->_description = obj.value("description").toString().toUtf8().constData();
    _st->_id = obj.value("id").toString().toUInt();
    _st->_done = IntToSTDoneType(obj.value("done").toString().toInt());
    _st->_timeCreation = obj.value("timeCreation").toString().toULongLong();
    _st->_timeDone = obj.value("timeDone").toString().toULongLong();
    _st->_timeDue = obj.value("timeDue").toString().toULongLong();
    _st->_priority = obj.value("priority").toString().toInt();
    _st->_level = obj.value("level").toString().toUInt();

    //_st->setName(obj.value("name").toString().toUtf8().constData());
    //_st->setDescription(obj.value("description").toString().toUtf8().constData());
    //_st->setId(obj.value("id").toString().toUInt());
    //_st->setDone(IntToSTDoneType(obj.value("done").toString().toInt()));
    //_st->setTimeCreation(obj.value("timeCreation").toString().toULongLong());
    //_st->setTimeDone(obj.value("timeDone").toString().toULongLong());
    //_st->setTimeDue(obj.value("timeDue").toString().toULongLong());
    //_st->setPriority(obj.value("priority").toString().toInt());
    //_st->setLevel(obj.value("level").toString().toUInt());

    QJsonArray subTasks = obj.value("subTasks").toArray();

    for(auto i = subTasks.begin(); i != subTasks.end(); ++i)
    {
        QJsonValue subTask = *i;
        SimpleTask *_subTask = STFromJSON(subTask.toObject(), _st);
        //check check check
        _st->addSubTask(_subTask);
    }

    return _st;
}

SimpleTask *SimpleTaskManager::STFromQString(QString st)
{
    QJsonDocument doc;
    doc = QJsonDocument::fromJson(st.toUtf8());

    QJsonObject obj;
    obj = doc.object();

    SimpleTask *_st = STFromJSON(obj);

    return _st;
}

SimpleTask *SimpleTaskManager::STFromBinary(QByteArray st)
{
#ifdef COMPRESS
    return STFromQString(qUncompress(st));
#else
    return STFromQString(QString(st));
#endif

}

QString SimpleTaskManager::STGetTaskFileName(string dir, SimpleTask *task)
{
    QString _dir(dir.c_str());
    if(_dir == "")
        _dir = ".";

    return QString(_dir) + "/" + QString(QString::number(task->id()) + "-" + task->name().c_str()) + ".stb";
}

QString SimpleTaskManager::STGetTaskFileOldName(string dir, SimpleTask *task)
{
    if(task->oldName() != "")
    {
        QString _dir(dir.c_str());
        if(_dir == "")
            _dir = ".";

        return QString(_dir) + "/" + QString(QString::number(task->id()) + "-" + task->oldName().c_str()) + ".stb";
    }
    else
    {
        return "";
    }
}

void SimpleTaskManager::STSaveToFile(string dir, SimpleTask *task)
{
    QString oldName = STGetTaskFileOldName(dir, task);
    if(oldName != "")
    {
        QFile::remove(oldName);
    }

    QByteArray data = STToBinary(task);
    QFile f(STGetTaskFileName(dir, task));
    f.open(QIODevice::Truncate | QIODevice::WriteOnly);
    f.write(data);
}

int SimpleTaskManager::STDoneTypeToInt(STDoneType val)
{
    int ret;

    switch(val)
    {
    case NOTDONE:
        ret = 0;
        break;
    case DONE:
        ret = 1;
        break;
    default:
        ret = 0;
        break;
    }

    return ret;
}

STDoneType SimpleTaskManager::IntToSTDoneType(int val)
{
    STDoneType ret;

    switch(val)
    {
    case 0:
        ret = NOTDONE;
        break;
    case 1:
        ret = DONE;
        break;
    default:
        ret = NOTDONE;
        break;
    }

    return ret;
}
