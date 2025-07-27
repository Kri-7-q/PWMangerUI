#ifndef SHOWACCOUNT_H
#define SHOWACCOUNT_H

#include "accountdialog.h"

class ShowAccount : public AccountDialog
{
    Q_OBJECT

public:
    ShowAccount(QWidget *parent=nullptr);
};

#endif // SHOWACCOUNT_H
