#ifndef STRINGLISTJOINER_H
#define STRINGLISTJOINER_H

#include <QString>

QString joinStringList(const QStringList list, QString delimiter = ",", QString prefix=QString(), QString postfix=QString());

#endif // STRINGLISTJOINER_H
