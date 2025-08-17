#include "accountdialog.h"
#include "mainwindow.h"
#include "ui_accountdialog.h"
#include "Model/modelindexiterator.h"

#include <QClipboard>
#include <QStatusBar>

AccountDialog::AccountDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AccountDialog)
{
    ui->setupUi(this);
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
    index_ = index;
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

void AccountDialog::clear()
{
    ui->edId->clear();
    ui->edProvider->clear();
    ui->edUsername->clear();
    ui->edPassword->clear();
    ui->edPasswdLength->clear();
    ui->edPasswdDefinition->clear();
    ui->edQuestion->clear();
    ui->edAnswer->clear();
    ui->edLastModified->clear();
}

void AccountDialog::statusBarMsg(const QString &msg, int msec) const
{
    MainWindow *mw = static_cast<MainWindow*>(parent());
    mw->statusBar()->showMessage(msg, msec);
}

QVariant AccountDialog::fieldValue(DBField field) const
{
    QVariant val;
    switch (field) {
    case DBField::Id:
        val = ui->edId->text().toInt();
        break;
    case DBField::Provider:
        val = ui->edProvider->text();
        break;
    case DBField::Username:
        val = ui->edUsername->text();
        break;
    case DBField::Password:
        val = ui->edPassword->text();
        break;
    case DBField::PasswordLength:
        val = ui->edPasswdLength->text().toInt();
        break;
    case DBField::PasswordDefinition:
        val = ui->edPasswdDefinition->text();
        break;
    case DBField::Question:
        val = ui->edQuestion->text();
        break;
    case DBField::Answer:
        val = ui->edAnswer->text();
        break;
    case DBField::LastModified:
        val = ui->edLastModified->dateTime();
        break;
    default:
        break;
    }

    return val;
}
