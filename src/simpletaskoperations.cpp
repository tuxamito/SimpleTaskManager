#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QByteArray>
#include <QFile>

#include <QDebug>

#include "simpletaskoperations.h"

QString STToQString(SimpleTask *st)
{
    QJsonDocument doc;
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

    doc.setObject(obj);

    return QString(doc.toJson());
}

QByteArray STToBinary(SimpleTask *st)
{
    return qCompress(STToQString(st).toUtf8());
}

SimpleTask *STFromQString(QString st)
{
    SimpleTask *_st;
    _st = new SimpleTask;

    QJsonDocument doc;
    doc = QJsonDocument::fromJson(st.toUtf8());

    QJsonObject obj;
    obj = doc.object();

    _st->setName(obj.value("name").toString().toUtf8().constData());
    _st->setDescription(obj.value("description").toString().toUtf8().constData());
    _st->setId(obj.value("id").toString().toUInt());
    _st->setDone(IntToSTDoneType(obj.value("done").toString().toInt()));
    _st->setTimeCreation(obj.value("timeCreation").toString().toULongLong());
    _st->setTimeDone(obj.value("timeDone").toString().toULongLong());
    _st->setTimeDue(obj.value("timeDue").toString().toULongLong());
    _st->setPriority(obj.value("priority").toString().toInt());
    _st->setPriority(obj.value("level").toString().toUInt());

    return _st;
}

SimpleTask *STFromBinary(QByteArray st)
{
    return STFromQString(qUncompress(st));
}

QString STGetTaskFileName(string dir, SimpleTask *task)
{
    QString _dir(dir.c_str());
    if(_dir == "")
        _dir = ".";

    return QString(_dir) + "/" + QString(QString::number(task->id()) + "-" + task->name().c_str()) + ".stb";
}

QString STGetTaskFileOldName(string dir, SimpleTask *task)
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

void STSaveToFile(string dir, SimpleTask *task)
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

int STDoneTypeToInt(STDoneType val)
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

STDoneType IntToSTDoneType(int val)
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
