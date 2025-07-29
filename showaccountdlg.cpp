#include "showaccountdlg.h"
#include "ui_accountdialog.h"
#include "mainwindow.h"
#include "enumapp.h"

ShowAccount::ShowAccount(QWidget *parent)
    : AccountDialog(parent)
{
    setObjectName("ShowAccount");
    MainWindow *mainWindow = qobject_cast<MainWindow*>(parent);
    connect(getUi()->btnOK, &QPushButton::clicked, [mainWindow]() { mainWindow->changeViewFromTo(View::ShowAccountDlg, View::AccountList); });
}
