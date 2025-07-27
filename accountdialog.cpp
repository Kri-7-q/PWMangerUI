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
    ui->edId->setText(indexIt.dataAndNextColumn().toString());
    ui->edProvider->setText(indexIt.dataAndNextColumn().toString());
    ui->edUsername->setText(indexIt.dataAndNextColumn().toString());
    ui->edPassword->setText(indexIt.dataAndNextColumn().toString());
    ui->edPasswdLength->setText(indexIt.dataAndNextColumn().toString());
    ui->edPasswdDefinition->setText(indexIt.dataAndNextColumn().toString());
    ui->edQuestion->setText(indexIt.dataAndNextColumn().toString());
    ui->edAnswer->setText(indexIt.dataAndNextColumn().toString());
    ui->edLastModified->setDateTime(indexIt.dataAndNextColumn().toDateTime());
}

/*
 * Set the password from QLineEdit into Clipborad.
 */
void AccountDialog::setPasswordToCLipboard()
{
    QClipboard *c = QGuiApplication::clipboard();
    c->setText(ui->edPassword->text());
}
