#include "sqlpersistance.h"

#include <QSqlField>
#include <QSqlRecord>
#include <QSqlDriver>
#include <QSqlError>

SqlPersistance::SqlPersistance()
{

}

/*
 * Get a Database connection with given credentials.
 */
QSqlDatabase SqlPersistance::databaseWithCredentials(const Credentials &credentials)
{
    if (QSqlDatabase::contains(credentials.value(Credentials::DatabaseName)))
        return QSqlDatabase::database(credentials.value(Credentials::DatabaseName), true);
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL", credentials.value(Credentials::DatabaseName));
    db.setHostName(credentials.value(Credentials::Hostname));
    db.setPort(credentials.value(Credentials::Port).toInt());
    db.setDatabaseName(credentials.value(Credentials::DatabaseName));
    db.setUserName(credentials.value(Credentials::Username));
    db.setPassword(credentials.value(Credentials::Password));
    db.open();

    return db;
}

/*
 * Create a Select Statement String.
 */
QString SqlPersistance::sqlSelectStatement(const QSqlDatabase &db, const QString &tablename)
{
    QSqlRecord record = db.record(tablename);
    int index = record.indexOf("userid");
    QSqlField field = record.field(index);
    record.remove(index);
    QSqlRecord whereRecord;
    field.setValue(1);
    whereRecord.append(field);
    QString stmt = db.driver()->sqlStatement(QSqlDriver::SelectStatement, tablename, record, false);
    stmt += db.driver()->sqlStatement(QSqlDriver::WhereStatement, tablename, whereRecord, false);

    return stmt;
}

/*
 * Get the Databes Error as a String.
 */
QString SqlPersistance::databaseError(const QSqlDatabase &db)
{
    QSqlError error = db.driver()->lastError();
    QString msg = error.text();
    msg += '\n';
    msg += error.databaseText();
    msg += '\n';
    msg += error.driverText();
    msg += '\n';

    return msg;
}

/*
 * Get Values from a QSqlRecord with Enums.
 */
QVariant SqlPersistance::dataFromSqlResult(const QSqlRecord &result, DBField field)
{
    QVariant data;
    switch (field)
    {
    case DBField::Id:
        data = result.field("id").value();
        break;
    case DBField::Provider:
        data = result.field("provider").value();
        break;
    case DBField::Username:
        data = result.field("username").value();
        break;
    case DBField::Password:
        data = result.field("password").value();
        break;
    case DBField::PasswordLength:
        data = result.field("passwordlength").value();
        break;
    case DBField::PasswordDefinition:
        data = result.field("definedcharacter").value();
        break;
    case DBField::Question:
        data = result.field("question").value();
        break;
    case DBField::Answer:
        data = result.field("answer").value();
        break;
    case DBField::LastModified:
        data = result.field("lastmodify").value();
    }
    return data;
}
