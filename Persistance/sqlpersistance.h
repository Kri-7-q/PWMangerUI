#ifndef SQLPERSISTANCE_H
#define SQLPERSISTANCE_H

#include "credentials.h"
#include "enumeration.h"
#include "qsqlrecord.h"

#include <QSqlDatabase>

class SqlPersistance
{
public:
    SqlPersistance();

    static QSqlDatabase databaseWithCredentials(const Credentials &credentials);
    static QString sqlSelectStatement(const QSqlDatabase &db, const QString &tablename, QSqlRecord whereClause=QSqlRecord());
    static QString sqlInsertStatement(const QSqlRecord &record, bool prepared=true);
    static QString sqlUpdateStatement(QSqlDatabase &db, const QSqlRecord &record, const QSqlRecord &whereClause, bool prepared=true);
    static QString databaseError(const QSqlDatabase &db);
    static QVariant dataFromSqlResult(const QSqlRecord &record, DBField field);
    static void setDataToRecord(QSqlRecord &record, DBField field, const QString &val);
    static void setDataToRecord(QSqlRecord &record, DBField field, const int val);
    static void setDataToRecord(QSqlRecord &record, DBField field, QVariant val);
    static void setDataToRecordIfModified(QSqlRecord &record, DBField field, QVariant &oldVal, QVariant &newVal);
    static QString dbFieldName(DBField field);
    static Credentials getCredentials();
};

#endif // SQLPERSISTANCE_H
