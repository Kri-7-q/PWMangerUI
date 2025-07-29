#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include <QWidget>

namespace Ui {
class AccountDialog;
}

class QTreeWidgetItem;

class AccountDialog : public QWidget
{
    Q_OBJECT

public:
    explicit AccountDialog(QWidget *parent = nullptr);
    ~AccountDialog();

    void setItemData(QModelIndex index);
    Ui::AccountDialog* getUi() const { return ui; }

public slots:
    void setPasswordToCLipboard();

private:
    Ui::AccountDialog *ui;
};

#endif // ACCOUNTDIALOG_H
