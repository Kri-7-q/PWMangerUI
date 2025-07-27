#ifndef MODELINDEXITERATOR_H
#define MODELINDEXITERATOR_H

#include <QModelIndex>

class ModelIndexIterator
{
public:
    explicit ModelIndexIterator(const QModelIndex& index);

    QVariant dataAndNextColumn();

private:
    QModelIndex index_;
};

#endif // MODELINDEXITERATOR_H
