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

#include <QClipboard>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QStatusBar>


AccountListe::AccountListe(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountListe)
{
    ui->setupUi(this);
    connect(ui->btnShowCurrent, &QPushButton::clicked, [this]() { getMainWin()->changeViewFromTo(View::AccountList, View::ShowAccountDlg); });
    connect(ui->btnNew, &QPushButton::clicked, [this]() { getMainWin()->changeViewFromTo(View::AccountList, View::NewAccountDlg); });
    connect(ui->btnModify, &QPushButton::clicked, [this]() {getMainWin()->changeViewFromTo(View::AccountList, View::ModifyAccountDlg); });
    connect(ui->btnStartSearch, &QToolButton::clicked, this, &AccountListe::startSearch);
    connect(ui->btnCancelSearch, &QToolButton::clicked, this, &AccountListe::cancelSearch);
    connect(ui->btnCopyPwd, &QPushButton::clicked, this, &AccountListe::copyPassword);
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
    Credentials c = SqlPersistance::getCredentials();
    QSqlDatabase db = SqlPersistance::databaseWithCredentials(c);
    QString stmt = SqlPersistance::sqlSelectStatement(db, c.value(Credentials::Key::TableName));
    qDebug() << "Select-Statement:  " << stmt;
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
    disconnect(ui->twAccountList->selectionModel(), &QItemSelectionModel::selectionChanged, this, &AccountListe::enableButtons);
    connect(ui->twAccountList->selectionModel(), &QItemSelectionModel::selectionChanged, this, &AccountListe::enableButtons);
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

/*
 * Start a search in Provider list with the given text.
 */
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

/*
 * Reset the QtreeView and search QLineEdit field.
 */
void AccountListe::cancelSearch(bool)
{
    loadAccountList();
    ui->edSearch->clear();
}

/*
 * Copy password from current selected entry into clipboard.
 */
void AccountListe::copyPassword(bool) const
{
    QModelIndex index = getCurrentSelectedItem();
    if (!index.isValid())
    {
        getMainWin()->statusBar()->showMessage("Kein Eintrag selektiert!", 5000);
        return;
    }
    ModelIndexIterator indexIt(index);
    QApplication::clipboard()->setText(indexIt.data(DBField::Password).toString());
}

void AccountListe::enableButtons(const QItemSelection selected, const QItemSelection) const
{
    bool enable = !selected.isEmpty(); // ui->twAccountList->selectionModel()->hasSelection();
    ui->btnShowCurrent->setEnabled(enable);
    ui->btnCopyPwd->setEnabled(enable);
    ui->btnDelete->setEnabled(enable);
    ui->btnModify->setEnabled(enable);
}

/*
 * Get a pointer to MainWindow.
 */
MainWindow *AccountListe::getMainWin() const
{
    return static_cast<MainWindow*>(parent());
}
