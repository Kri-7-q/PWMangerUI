#include "accountliste.h"
#include "mainwindow.h"
#include "showaccount.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    AccountListe *widget = new AccountListe(&w);
    widget->loadAccountList();
    w.setCentralWidget(widget);
    ShowAccount *showWidget = new ShowAccount(&w);
    showWidget->hide();

    w.show();
    return a.exec();
}
