#include "accountliste.h"
#include "mainwindow.h"
#include "showaccountdlg.h"
#include "newaccountdlg.h"
#include "modifyaccountdlg.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    AccountListe *accountliste = new AccountListe(&w);
    accountliste->loadAccountList();
    w.setAccountListe(accountliste);
    w.setCentralWidget(accountliste);

    ShowAccount *showAccountDlg = new ShowAccount(&w);
    showAccountDlg->hide();
    w.setShowAccountDlg(showAccountDlg);

    NewAccountDlg *newAccountDlg = new NewAccountDlg(&w);
    newAccountDlg->hide();
    w.setNewAccountDlg(newAccountDlg);

    ModifyAccountDlg *modifyAccountDlf = new ModifyAccountDlg(&w);
    modifyAccountDlf->hide();
    w.setModifyAccountDlg(modifyAccountDlf);

    w.show();
    return a.exec();
}
