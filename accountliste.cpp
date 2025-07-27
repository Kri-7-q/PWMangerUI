#include "accountliste.h"
#include "Model/modelindexiterator.h"
#include "Persistance/sqlpersistance.h"
#include "Model/accountlistmodel.h"
#include "SearchAccount/matchobject.h"
#include "SearchAccount/matchstring.h"
#include "Utility/sortlist.h"
#include "mainwindow.h"
#include "ui_accountliste.h"
#include "Persistance/enumeration.h"

#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QStatusBar>

AccountListe::AccountListe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountListe)
{
    ui->setupUi(this);
    connect(ui->btnShowCurrent, &QPushButton::clicked, getMainWin(), &MainWindow::changeViewShowAccount);
    connect(ui->btnStartSearch, &QToolButton::clicked, this, &AccountListe::startSearch);
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
    QList<QSqlRecord> list;
    while (query.next())
    {
        list <<  query.record();
    }
    AccountListModel *model = new AccountListModel;
    model->setContent(list);
    ui->twAccountList->setModel(model);
}

/*
 * Get the current selected Item of AccountList.
 */
QModelIndex AccountListe::getCurrentSelectedItem() const
{
    if (ui->twAccountList->selectionModel()->hasSelection())
        return ui->twAccountList->selectionModel()->selectedIndexes().first();

    return {};
}

void AccountListe::startSearch(bool) const
{
    QString searchText = ui->edSearch->text();
    if (searchText.length() < 4)
    {
        getMainWin()->statusBar()->showMessage("Für die Suche werden wenigstens vier Zeichen benötigt!", 5000);
        return;
    }
    MatchString match(ui->edSearch->text());
    SortList<MatchObject> sortList;
    ModelIndexIterator indexIt( ui->twAccountList->model()->index(0, 0) );
    do
    {
        QString text = indexIt.data(DBField::Provider).toString();
        int matchResult = match.matchText(text);
        if (matchResult)
            sortList.insert(MatchObject(indexIt.currentRow(), matchResult));
        match.reset();
    } while (indexIt.nextRow());

    if (sortList.isEmpty())
    {
        getMainWin()->statusBar()->showMessage("Nichts gefunden!", 5000);
        return;
    }
    AccountListModel *model = static_cast<AccountListModel*>(ui->twAccountList->model());
    model->filterWithSortList(sortList);
}

MainWindow *AccountListe::getMainWin() const
{
    return static_cast<MainWindow*>(parent());
}
