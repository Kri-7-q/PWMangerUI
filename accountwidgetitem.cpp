#include "accountwidgetitem.h"

AccountWidgetItem::AccountWidgetItem(const QSqlRecord &record)
{
    setData(0, Qt::DisplayRole, record.value("id"));
    setData(1, Qt::DisplayRole, record.value("provider"));
    setData(2, Qt::DisplayRole, record.value("username"));
    sqlRecord_ = record;
}
