#include "mainwindow.h"
#include "accountliste.h"
#include "ui_mainwindow.h"
#include "showaccountdlg.h"
#include "newaccountdlg.h"
#include "modifyaccountdlg.h"

#include <QModelIndex>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeViewFromTo(View from, View to)
{
    // From
    switch (from) {
    case View::AccountList:
        accountlist_->hide();
        break;
    case View::ShowAccountDlg:
        showaccountdlg_->hide();
        break;
    case View::NewAccountDlg:
        newaccountdlg_->hide();
        break;
    case View::ModifyAccountDlg:
        modifyaccountdlg_->hide();
        break;
    default:
        break;
    }
    // To
    switch (to) {
    case View::ShowAccountDlg:
    {
        showAccountDlg(showaccountdlg_);
        break;
    }
    case View::AccountList:
        accountlist_->show();
        break;
    case View::NewAccountDlg:
        newaccountdlg_->show();
        break;
    case View::ModifyAccountDlg:
    {
        showAccountDlg(modifyaccountdlg_);
        break;
    }
    default:
        break;
    }
}

void MainWindow::showAccountDlg(AccountDialog *dlg)
{
    QModelIndex index = accountlist_->getCurrentSelectedItem();
    if (index.isValid())
    {
        dlg->setItemData(index);
        dlg->show();
    }
}

void MainWindow::setAccountListe(AccountListe *w)
{
    accountlist_ = w;
}

void MainWindow::setShowAccountDlg(ShowAccount *w)
{
    showaccountdlg_ = w;
}

void MainWindow::setNewAccountDlg(NewAccountDlg *w)
{
    newaccountdlg_ = w;
}

void MainWindow::setModifyAccountDlg(ModifyAccountDlg *w)
{
    modifyaccountdlg_ = w;
}
