#include "accountdialog.h"
#include "Persistance/sqlpersistance.h"
#include "accountwidgetitem.h"
#include "mainwindow.h"
#include "ui_accountdialog.h"

#include <QClipboard>

AccountDialog::AccountDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountDialog)
{
    ui->setupUi(this);
    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    connect(ui->btnOK, &QPushButton::clicked, mainWindow, &MainWindow::changeViewShowAccountList);
    connect(ui->btnCopyPasswd, &QPushButton::clicked, this, &AccountDialog::setPasswordToCLipboard);
}

AccountDialog::~AccountDialog()
{
    delete ui;
}


/* Set Data to the View.
 * The QTreeWidgetItem contain whole data of a Account.
 */
void AccountDialog::setItemData(const QTreeWidgetItem *i)
{
    const AccountWidgetItem *item = static_cast<const AccountWidgetItem*>(i);
    ui->edId->setText(SqlPersistance::dataFromSqlResult(item->getRecord(), DBField::Id).toString());
    ui->edProvider->setText(SqlPersistance::dataFromSqlResult(item->getRecord(), DBField::Provider).toString());
    ui->edUsername->setText(SqlPersistance::dataFromSqlResult(item->getRecord(), DBField::Username).toString());
    ui->edPassword->setText(SqlPersistance::dataFromSqlResult(item->getRecord(), DBField::Password).toString());
    ui->edPasswdLength->setText(SqlPersistance::dataFromSqlResult(item->getRecord(), DBField::PasswordLength).toString());
    ui->edPasswdDefinition->setText(SqlPersistance::dataFromSqlResult(item->getRecord(), DBField::PasswordDefinition).toString());
    ui->edQuestion->setText(SqlPersistance::dataFromSqlResult(item->getRecord(), DBField::Question).toString());
    ui->edAnswer->setText(SqlPersistance::dataFromSqlResult(item->getRecord(), DBField::Answer).toString());
    ui->edLastModified->setDateTime(SqlPersistance::dataFromSqlResult(item->getRecord(), DBField::LastModified).toDateTime());
}

/*
 * Set the password from QLineEdit into Clipborad.
 */
void AccountDialog::setPasswordToCLipboard()
{
    QClipboard *c = QGuiApplication::clipboard();
    c->setText(ui->edPassword->text());
}
