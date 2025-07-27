#include "accountdialog.h"
#include "mainwindow.h"
#include "ui_accountdialog.h"
#include "Model/modelindexiterator.h"

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
void AccountDialog::setItemData(QModelIndex index)
{
    ModelIndexIterator indexIt(index);
    ui->edId->setText(indexIt.data(DBField::Id).toString());
    ui->edProvider->setText(indexIt.data(DBField::Provider).toString());
    ui->edUsername->setText(indexIt.data(DBField::Username).toString());
    ui->edPassword->setText(indexIt.data(DBField::Password).toString());
    ui->edPasswdLength->setText(indexIt.data(DBField::PasswordLength).toString());
    ui->edPasswdDefinition->setText(indexIt.data(DBField::PasswordDefinition).toString());
    ui->edQuestion->setText(indexIt.data(DBField::Question).toString());
    ui->edAnswer->setText(indexIt.data(DBField::Answer).toString());
    ui->edLastModified->setDateTime(indexIt.data(DBField::LastModified).toDateTime());
}

/*
 * Set the password from QLineEdit into Clipborad.
 */
void AccountDialog::setPasswordToCLipboard()
{
    QClipboard *c = QGuiApplication::clipboard();
    c->setText(ui->edPassword->text());
}
