#include "accountliste.h"
#include "mainwindow.h"
#include "showaccountdlg.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    AccountListe *widget = new AccountListe(&w);
    widget->loadAccountList();
    w.setAccountListe(widget);
    w.setCentralWidget(widget);

    ShowAccount *showWidget = new ShowAccount(&w);
    showWidget->hide();
    w.setShowAccountDlg(showWidget);

    w.show();
    return a.exec();
}
