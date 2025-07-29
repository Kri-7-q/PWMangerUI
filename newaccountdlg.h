#ifndef NEWACCOUNTDLG_H
#define NEWACCOUNTDLG_H

#include "accountdialog.h"

class NewAccountDlg : public AccountDialog
{
public:
    NewAccountDlg(QWidget *parent=nullptr);

    void generatePassword(bool) const;
    void saveData() const;
};

#endif // NEWACCOUNTDLG_H
