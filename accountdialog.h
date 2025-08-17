#ifndef ACCOUNTDIALOG_H
#define ACCOUNTDIALOG_H

#include "Persistance/enumeration.h"

#include <QWidget>
#include <QModelIndex>

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

protected:
    void clear();
    void statusBarMsg(const QString &msg, int msec=5000) const;
    QVariant fieldValue(DBField field) const;

    QModelIndex index_;

private:
    Ui::AccountDialog *ui;
};

#endif // ACCOUNTDIALOG_H
