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
    const QTreeWidgetItem *item = cw->getCurrentSelectedItem();
    if (item)
        w->setItemData(item);
    w->show();
}

void MainWindow::changeViewShowAccountList()
{
    findChild<ShowAccount*>("ShowAccount")->hide();
    AccountListe *w = findChild<AccountListe*>("AccountListe");
    w->show();
}

