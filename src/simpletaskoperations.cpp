#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

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

}

SimpleTask *STFromBinary(QByteArray st)
{
    return STFromQString(QString(st));
}
