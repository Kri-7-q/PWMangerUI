#include "accountliste.h"
#include "Persistance/sqlpersistance.h"
#include "accountwidgetitem.h"
#include "mainwindow.h"
#include "ui_accountliste.h"

#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>

AccountListe::AccountListe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountListe)
{
    ui->setupUi(this);
    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    connect(ui->btnShowCurrent, &QPushButton::clicked, mainWindow, &MainWindow::changeViewShowAccount);
}

AccountListe::~AccountListe()
{
    delete ui;
}

/*
 * Liest die Daten aus der Datenbank.
 * The accounts are read completly an stored in QTreeWidgetItem as QSqlRecord.
 */
void AccountListe::loadAccountList()
{
    QString path = Credentials::usersHomePath() + "/.pwmanager";
    Credentials c = Credentials::credentialsFromFile(path);
    QSqlDatabase db = SqlPersistance::databaseWithCredentials(c);
    QString stmt = SqlPersistance::sqlSelectStatement(db, c.value(Credentials::TableName));
    QSqlQuery query(db);
    if (! query.exec(stmt))
    {
        QString err("Konnte die Query nicht ausführen!\n");
        err += stmt + '\n';
        err += SqlPersistance::databaseError(db);
        ui->lbMessage->setText(err);
    }
    while (query.next())
    {
        QSqlRecord r = query.record();
        AccountWidgetItem *item = new AccountWidgetItem(r);
        ui->twAccountList->addTopLevelItem(item);
    }
}

/*
 * Get the current selected Item of AccountList.
 */
const QTreeWidgetItem *AccountListe::getCurrentSelectedItem() const
{
    QList<QTreeWidgetItem*> itemList = ui->twAccountList->selectedItems();
    if (itemList.isEmpty())
        return nullptr;

    return itemList.first();
}
