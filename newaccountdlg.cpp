#include "newaccountdlg.h"
#include "mainwindow.h"
#include "qsqlrecord.h"
#include "ui_accountdialog.h"
#include "PasswordGenerator/pwgenerator.h"
#include "Persistance/sqlpersistance.h"

#include <QStatusBar>
#include <QSqlQuery>
#include <QSqlError>>

NewAccountDlg::NewAccountDlg(QWidget *parent)
    : AccountDialog(parent)
{
    setObjectName("NewAccountDlg");
    getUi()->edId->setEnabled(false);
    getUi()->lbLastModified->hide();
    getUi()->edLastModified->hide();
    getUi()->btnSaveData->show();
    getUi()->btnCopyPasswd->setText("Passwort generieren");
    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    connect(getUi()->btnOK, &QPushButton::clicked, [mainWindow]() { mainWindow->changeViewFromTo(View::NewAccountDlg, View::AccountList); });
    connect(getUi()->btnCopyPasswd, &QPushButton::clicked, this, &NewAccountDlg::generatePassword);
    connect(getUi()->btnSaveData, &QPushButton::clicked, this, &NewAccountDlg::saveData);
}

void NewAccountDlg::generatePassword(bool) const
{
    PwGenerator generator;
    unsigned int length = getUi()->edPasswdLength->text().toUInt();
    QString definition = getUi()->edPasswdDefinition->text();
    QString passwd = generator.passwordFromDefinition(length, definition);
    if (generator.hasError())
    {
        MainWindow *mainWindow = qobject_cast<MainWindow*>(parent());
//        mainWindow->statusBar()->showMessage("Es muss ein Wert für die Passwortlänge und eine Definition der Zeichen eingegeben werden!");
        mainWindow->statusBar()->showMessage(generator.errorMessage());
        return;
    }
    getUi()->edPassword->setText(passwd);
}

void NewAccountDlg::saveData() const
{
    QSqlRecord record;
    SqlPersistance::setDataToRecord(record, DBField::Provider, getUi()->edProvider->text());
    SqlPersistance::setDataToRecord(record, DBField::Username, getUi()->edUsername->text());
    SqlPersistance::setDataToRecord(record, DBField::Password, getUi()->edPassword->text());
    QString lengthVal = getUi()->edPasswdLength->text();
    if (!lengthVal.isEmpty())
        SqlPersistance::setDataToRecord(record, DBField::PasswordLength, lengthVal.toInt());
    SqlPersistance::setDataToRecord(record, DBField::PasswordDefinition, getUi()->edPasswdDefinition->text());
    SqlPersistance::setDataToRecord(record, DBField::Question ,getUi()->edQuestion->text());
    SqlPersistance::setDataToRecord(record, DBField::Answer, getUi()->edAnswer->text());
    SqlPersistance::setDataToRecord(record, DBField::UserId, 1);
    if (record.count() < 1)
    {
        MainWindow *mainWindow = qobject_cast<MainWindow*>(parent());
        mainWindow->statusBar()->showMessage("Es gibt nichts zu speichern!");
        return;
    }
    SqlPersistance::setDataToRecord(record, DBField::LastModified, QVariant(QDateTime::currentDateTime()));
    QString stmt = SqlPersistance::sqlInsertStatement(record);
    qDebug() << stmt;
    QSqlDatabase db = SqlPersistance::databaseWithCredentials(SqlPersistance::getCredentials());
    QSqlQuery query(db);
    if (!query.prepare(stmt))
    {
        qDebug() << query.lastError().text();
        return;
    }
    for (int i=0; i<record.count(); ++i)
        query.bindValue(":"+record.fieldName(i), record.value(i));
    if (!query.exec())
    {
        qDebug() << query.lastError().text();
    }
}
