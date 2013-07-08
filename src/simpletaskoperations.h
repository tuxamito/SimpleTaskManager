#ifndef SIMPLETASKOPERATIONS_H
#define SIMPLETASKOPERATIONS_H

#include <QString>
#include <QByteArray>

#include "simpletask.h"

QString STToQString(SimpleTask *st);
QByteArray STToBinary(SimpleTask *st);

SimpleTask *STFromQString(QString st);
SimpleTask *STFromBinary(QByteArray st);

#endif // SIMPLETASKOPERATIONS_H
