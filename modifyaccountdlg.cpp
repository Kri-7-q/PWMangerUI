#include "modifyaccountdlg.h"
#include "mainwindow.h"
#include "ui_accountdialog.h"
#include "PasswordGenerator/pwgenerator.h"
#include "Persistance/sqlpersistance.h"
#include "Model/modelindexiterator.h"

#include <QSqlQuery>
#include <QSqlError>

ModifyAccountDlg::ModifyAccountDlg(QWidget *parent)
    : AccountDialog(parent)
{
    setObjectName("ModifyAccount");
    getUi()->btnCopyPasswd->setText("Passwort generieren");
    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    connect(getUi()->btnOK, &QPushButton::clicked, [mainWindow]() { mainWindow->changeViewFromTo(View::ModifyAccountDlg, View::AccountList); });
    connect(getUi()->btnCopyPasswd, &QPushButton::clicked, this, &ModifyAccountDlg::generatePassword);
    connect(getUi()->btnSaveData, &QPushButton::clicked, this, &ModifyAccountDlg::saveChanges);
}

QSqlRecord ModifyAccountDlg::getModifications() const
{
    QSqlRecord record;
    ModelIndexIterator indexIt(index_);
    for (DBField field : {DBField::Provider, DBField::Username, DBField::Password, DBField::PasswordLength, DBField::PasswordDefinition, DBField::Question, DBField::Answer})
    {
        QVariant oldVal = indexIt.data(field);
        QVariant newVal = fieldValue(field);
        SqlPersistance::setDataToRecordIfModified(record, field, oldVal, newVal);
    }

    return record;
}

void ModifyAccountDlg::generatePassword(bool)
{
    PwGenerator generator;
    unsigned int length = getUi()->edPasswdLength->text().toUInt();
    QString definition = getUi()->edPasswdDefinition->text();
    QString passwd = generator.passwordFromDefinition(length, definition);
    if (generator.hasError())
    {
        statusBarMsg("Es muss ein Wert für die Passwortlänge und eine Definition der Zeichen eingegeben werden!");
        return;
    }
    getUi()->edPassword->setText(passwd);
}

void ModifyAccountDlg::saveChanges(bool)
{
    QSqlRecord record = getModifications();
    // Save into DB.
    ModelIndexIterator indexIt(index_);
    SqlPersistance::setDataToRecord(record, DBField::LastModified, QDateTime::currentDateTime());
    QSqlRecord whereClause;
    SqlPersistance::setDataToRecord(whereClause, DBField::Id, indexIt.data(DBField::Id));
    SqlPersistance::setDataToRecord(whereClause, DBField::UserId, QVariant(1));
    Credentials c = SqlPersistance::getCredentials();
    QSqlDatabase db = QSqlDatabase::database(c.value(Credentials::DatabaseName));
    QString stmt = SqlPersistance::sqlUpdateStatement(db, record, whereClause);
    QSqlQuery query(db);
    if (!query.prepare(stmt))
    {
        statusBarMsg(db.lastError().text());
        return;
    }
    for (int index = 0; index < record.count(); ++index)
    {
        QString bindName = ':' + record.fieldName(index);
        qDebug() << "Bind: " << bindName << "      Val: " << record.value(index);
        query.bindValue(bindName, record.value(index));
    }
    if (!query.exec())
    {
        statusBarMsg(db.lastError().text());
        return;
    }
    // Load from DB and set into model.
    whereClause.clear();
    SqlPersistance::setDataToRecord(whereClause, DBField::Id, fieldValue(DBField::Id));
    stmt = SqlPersistance::sqlSelectStatement(db, c.value(Credentials::TableName), whereClause);
    if (!query.exec(stmt))
    {
        statusBarMsg(db.lastError().text());
        return;
    }
    // Set into model
    if (!query.next())
    {
        statusBarMsg("Konnte den Eintrag mit der Änderung nicht finden!");
        return;
    }
    QSqlRecord resultRec = query.record();
    for (DBField field : { DBField::Id, DBField::Provider, DBField::Username, DBField::Password, DBField::PasswordLength,
                           DBField::PasswordDefinition, DBField::Question, DBField::Answer, DBField::LastModified, DBField::UserId})
    {
        QString fieldName = SqlPersistance::dbFieldName(field);
        QVariant val = resultRec.value(fieldName);
        indexIt.setData(field, val);
    }
}
