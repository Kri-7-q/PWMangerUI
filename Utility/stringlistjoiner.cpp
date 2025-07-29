#include "stringlistjoiner.h"

#include <QStringList>

QString joinStringList(const QStringList list, QString delimiter, QString prefix, QString postfix)
{
    QString joinedText;
    for (const QString &element : list)
    {
        if (!joinedText.isEmpty())
            joinedText += delimiter;
        joinedText += prefix;
        joinedText += element;
        joinedText += postfix;
    }

    return joinedText;
}
