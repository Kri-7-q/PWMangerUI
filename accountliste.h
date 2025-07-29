#ifndef ACCOUNTLISTE_H
#define ACCOUNTLISTE_H

#include "enumapp.h"

#include <QWidget>
#include <QItemSelection>

namespace Ui {
class AccountListe;
}
class MainWindow;

class AccountListe : public QWidget
{
    Q_OBJECT

public:
    explicit AccountListe(QWidget *parent = nullptr);
    ~AccountListe();

    void loadAccountList();
    QModelIndex getCurrentSelectedItem() const;

public slots:
    void startSearch(bool) const;
    void cancelSearch(bool);
    void copyPassword(bool) const;
    void enableButtons(const QItemSelection selected, const QItemSelection disselected) const;

private:
    MainWindow* getMainWin() const;

private:
    Ui::AccountListe *ui;
};

#endif // ACCOUNTLISTE_H
