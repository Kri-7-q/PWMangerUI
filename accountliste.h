#ifndef ACCOUNTLISTE_H
#define ACCOUNTLISTE_H

#include "qtreewidget.h"
#include <QWidget>

namespace Ui {
class AccountListe;
}

class AccountListe : public QWidget
{
    Q_OBJECT

public:
    explicit AccountListe(QWidget *parent = nullptr);
    ~AccountListe();

    void loadAccountList();
    const QTreeWidgetItem* getCurrentSelectedItem() const;

private:
    Ui::AccountListe *ui;
};

#endif // ACCOUNTLISTE_H
