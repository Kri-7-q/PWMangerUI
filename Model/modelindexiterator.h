#ifndef MODELINDEXITERATOR_H
#define MODELINDEXITERATOR_H

#include "Persistance/sqlpersistance.h"

#include <QModelIndex>

class ModelIndexIterator
{
public:
    explicit ModelIndexIterator(const QModelIndex& index);

    QVariant data(DBField field);
    void setData(DBField field, QVariant &val);
    bool nextRow();
    int currentRow() const { return index_.row(); }
    bool hasNext() const { return index_.isValid(); }

private:
    QModelIndex index_;
};

#endif // MODELINDEXITERATOR_H
