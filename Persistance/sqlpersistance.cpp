#include "sqlpersistance.h"
#include "Utility/stringlistjoiner.h"

#include <QSqlField>
#include <QSqlRecord>
#include <QSqlDriver>
#include <QSqlError>



SqlPersistance::SqlPersistance()
{

}

QHash<DBField, QString> fieldNames_ = {
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
QString SqlPersistance::sqlSelectStatement(const QSqlDatabase &db, const QString &tablename, QSqlRecord whereClause)
{
    QSqlRecord record = db.record(tablename);
    int index = record.indexOf(dbFieldName(DBField::UserId));       // Don't query the user. Select by user.
    QSqlField field = record.field(index);
    record.remove(index);
    field.setValue(1);          // Has to be fixed. Handles just one User.
    whereClause.append(field);
    QString stmt = db.driver()->sqlStatement(QSqlDriver::SelectStatement, tablename, record, false);
    stmt += ' ';
    stmt += db.driver()->sqlStatement(QSqlDriver::WhereStatement, tablename, whereClause, false);

    return stmt;
}

QString SqlPersistance::sqlInsertStatement(const QSqlRecord &record, bool prepared)
{
    Credentials c = getCredentials();
    QString stmt = "INSERT INTO \"%1\" (%2) VALUES (%3)";
    QStringList fields;
    QStringList vals;
    for (int index = 0; index < record.count(); ++index)
    {
        const QSqlField f = record.field(index);
        if (!f.isGenerated())
            continue;
        fields << f.name();
        if (prepared)
            vals << f.name();
        else
            vals << f.value().toString();
    }
    QString into = joinStringList(fields, ", ", "\"", "\"");
    QString values;
    if (prepared)
        values = joinStringList(vals, ", ", ":");
    else
        values = joinStringList(vals, ", ", "'", "'");   // !!!! Ist so nicht ausreichend !!! Datentypen: VALUES (1, 'hallo', <datum>)

    return stmt.arg(c.value(Credentials::Key::TableName)).arg(into).arg(values);
}

QString SqlPersistance::sqlUpdateStatement(QSqlDatabase &db, const QSqlRecord &record, const QSqlRecord &whereClause, bool prepared)
{
    Credentials c = getCredentials();
    QString stmt = "UPDATE \"";
    stmt += c.value(Credentials::TableName);
    stmt += "\" SET ";
    QStringList fields;
    for (int index = 0; index < record.count(); ++index)
    {
        const QSqlField f = record.field(index);
        if (!f.isGenerated())
            continue;
        QString field = "\"";
        field += f.name();
        field += "\"";
        field += " = ";
        if (prepared)
        {
            field += ':';
            field += f.name();
        }
        else
        {
            field += "'";
            field += f.value().toString();
            field += "'";
        }
        fields << field;
    }
    stmt += joinStringList(fields, ", ");
    stmt += ' ';
    stmt += db.driver()->sqlStatement(QSqlDriver::WhereStatement, c.value(Credentials::TableName), whereClause, false);

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
QVariant SqlPersistance::dataFromSqlResult(const QSqlRecord &record, DBField field)
{
    return record.value(dbFieldName(field));
}

void SqlPersistance::setDataToRecord(QSqlRecord &record, DBField field, QVariant val)
{
    QString fieldName = dbFieldName(field);
    int index = record.indexOf(fieldName);
    QSqlField f(fieldName);
    f.setValue(val);
    if (index >= 0)
        record.replace(index, f);
    else
        record.append(f);
}

void SqlPersistance::setDataToRecordIfModified(QSqlRecord &record, DBField field, QVariant &oldVal, QVariant &newVal)
{
    if (oldVal != newVal)
        setDataToRecord(record, field, newVal);
}

QString SqlPersistance::dbFieldName(DBField field)
{
    return fieldNames_[field];
}

Credentials SqlPersistance::getCredentials()
{
//    static Credentials credentials_ = Credentials::credentialsFromFile(Credentials::usersHomePath() + "/.pwmanager");
    static Credentials credentials_ = Credentials::credentialsFromFile(Credentials::usersHomePath() + "/.pwmtest");

    return credentials_;
}

void SqlPersistance::setDataToRecord(QSqlRecord &record, DBField field, const QString &val)
{
    if (val.isEmpty())
        return;
    setDataToRecord(record, field, QVariant(val));
}

void SqlPersistance::setDataToRecord(QSqlRecord &record, DBField field, const int val)
{
    setDataToRecord(record, field, QVariant(val));
}
