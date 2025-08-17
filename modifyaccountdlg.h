#ifndef MODIFYACCOUNTDLG_H
#define MODIFYACCOUNTDLG_H

#include "accountdialog.h"
#include <QSqlRecord>

class ModifyAccountDlg : public AccountDialog
{
public:
    ModifyAccountDlg(QWidget *parent=nullptr);

private:
    QSqlRecord getModifications() const;

signals:
    void generatePassword(bool);
    void saveChanges(bool);
};

#endif // MODIFYACCOUNTDLG_H
