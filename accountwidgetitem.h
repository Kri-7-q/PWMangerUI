#ifndef ACCOUNTWIDGETITEM_H
#define ACCOUNTWIDGETITEM_H

#include "qsqlrecord.h"

#include <QTreeWidgetItem>

class AccountWidgetItem : public QTreeWidgetItem
{
public:
    explicit AccountWidgetItem(const QSqlRecord &record);
    const QSqlRecord& getRecord() const { return sqlRecord_; }

private:
    QSqlRecord sqlRecord_;
};

#endif // ACCOUNTWIDGETITEM_H
