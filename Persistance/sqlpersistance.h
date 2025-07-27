#ifndef SQLPERSISTANCE_H
#define SQLPERSISTANCE_H

#include "credentials.h"
#include "qsqldriver.h"
#include "enumeration.h"

#include <QSqlDatabase>

class SqlPersistance
{
public:
    SqlPersistance();

    static QSqlDatabase databaseWithCredentials(const Credentials &credentials);
    static QString sqlSelectStatement(const QSqlDatabase &db, const QString &tablename);
    static QString databaseError(const QSqlDatabase &db);
    static QVariant dataFromSqlResult(const QSqlRecord &result, DBField field);
    static QHash<DBField, QString> _fieldNames;
};

#endif // SQLPERSISTANCE_H
