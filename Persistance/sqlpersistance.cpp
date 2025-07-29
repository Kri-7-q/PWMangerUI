#include "sqlpersistance.h"

#include <QSqlField>
#include <QSqlRecord>
#include <QSqlDriver>
#include <QSqlError>

SqlPersistance::SqlPersistance()
{

}

QHash<DBField, QString> SqlPersistance::_fieldNames = {
    {DBField::Id, "id"},
    {DBField::Provider, "provider"},
    {DBField::Username, "username"},
    {DBField::Password, "password"},
    {DBField::PasswordLength, "passwordlength"},
    {DBField::PasswordDefinition, "definedcharacter"},
    {DBField::Question, "question"},
    {DBField::Answer, "answer"},
    {DBField::LastModified, "lastmodify"},
    {DBField::UserId, "userid"},
};

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
    field.setValue(1);          // Has to be fixed. Handles just one User.
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
    return result.value(_fieldNames[field]);
}
