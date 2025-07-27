#include "mainwindow.h"
#include "accountliste.h"
#include "ui_mainwindow.h"
#include "showaccount.h"

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

void MainWindow::changeViewShowAccount()
{
    AccountListe *cw = findChild<AccountListe*>("AccountListe");
    cw->hide();
    ShowAccount *w = findChild<ShowAccount*>("ShowAccount");
    QModelIndex index = cw->getCurrentSelectedItem();
    if (index.isValid())
        w->setItemData(index);
    w->show();
}

void MainWindow::changeViewShowAccountList()
{
    findChild<ShowAccount*>("ShowAccount")->hide();
    AccountListe *w = findChild<AccountListe*>("AccountListe");
    w->show();
}

