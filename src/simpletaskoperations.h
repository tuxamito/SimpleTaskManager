#ifndef SIMPLETASKOPERATIONS_H
#define SIMPLETASKOPERATIONS_H

#include <QString>
#include <QByteArray>

#include "simpletask.h"

QString STToQString(SimpleTask *st);
QByteArray STToBinary(SimpleTask *st);

SimpleTask *STFromQString(QString st);
SimpleTask *STFromBinary(QByteArray st);

void STSaveToFile(string dir, SimpleTask *task);

int STDoneTypeToInt(STDoneType val);
STDoneType IntToSTDoneType(int val);

#endif // SIMPLETASKOPERATIONS_H
