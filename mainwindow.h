#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "enumapp.h"

#include <QMainWindow>
#include <QPointer>

class AccountListe;
class ShowAccount;
class NewAccountDlg;
class ModifyAccountDlg;
class AccountDialog;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void changeViewFromTo(View from, View to);
    void showAccountDlg(AccountDialog *dlg);
    void setAccountListe(AccountListe *w);
    void setShowAccountDlg(ShowAccount *w);
    void setNewAccountDlg(NewAccountDlg *w);
    void setModifyAccountDlg(ModifyAccountDlg *w);

private:
    Ui::MainWindow *ui;
    QPointer<AccountListe> accountlist_ = nullptr;
    QPointer<ShowAccount> showaccountdlg_ = nullptr;
    QPointer<NewAccountDlg> newaccountdlg_ = nullptr;
    QPointer<ModifyAccountDlg> modifyaccountdlg_ = nullptr;
};
#endif // MAINWINDOW_H
