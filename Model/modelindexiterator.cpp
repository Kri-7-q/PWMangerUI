#include "modelindexiterator.h"

ModelIndexIterator::ModelIndexIterator(const QModelIndex &index)
    : index_(index)
{

}

QVariant ModelIndexIterator::data(DBField field)
{
    QModelIndex i = index_.model()->index(index_.row(), static_cast<int>(field));

    return i.data();
}

bool ModelIndexIterator::nextRow()
{
    auto model = index_.model();
    index_ = model->index(index_.row()+1, index_.column());

    return index_.isValid();
}
