#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

#include <QDebug>

#include "simpletaskoperations.h"

QString STToQString(SimpleTask *st)
{
    QJsonDocument doc;
    QJsonObject obj;

    obj.insert("id", QJsonValue(QString::number(st->id())));
    obj.insert("name", QJsonValue(QString(st->name().c_str())));
    obj.insert("done", QJsonValue(st->done()));

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
    _st->setId(obj.value("id").toString().toUInt());

    return _st;
}

SimpleTask *STFromBinary(QByteArray st)
{
    return STFromQString(qUncompress(st));
}
