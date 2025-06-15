#ifndef SHOWACCOUNT_H
#define SHOWACCOUNT_H

#include <QWidget>

namespace Ui {
class ShowAccount;
}

class QTreeWidgetItem;

class ShowAccount : public QWidget
{
    Q_OBJECT

public:
    explicit ShowAccount(QWidget *parent = nullptr);
    ~ShowAccount();

    void setItemData(const QTreeWidgetItem* i);

public slots:
    void setPasswordToCLipboard();

private:
    Ui::ShowAccount *ui;
};

#endif // SHOWACCOUNT_H
