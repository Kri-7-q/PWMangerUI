#include "mainwindow.h"
#include "accountliste.h"
#include "ui_mainwindow.h"
#include "showaccountdlg.h"
#include "newaccountdlg.h"

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
    default:
        break;
    }
    // To
    switch (to) {
    case View::ShowAccountDlg:
    {
        QModelIndex index = accountlist_->getCurrentSelectedItem();
        if (index.isValid())
        {
            showaccountdlg_->setItemData(index);
            showaccountdlg_->show();
        }
        break;
    }
    case View::AccountList:
        accountlist_->show();
        break;
    case View::NewAccountDlg:
        newaccountdlg_->show();
        break;
    default:
        break;
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
