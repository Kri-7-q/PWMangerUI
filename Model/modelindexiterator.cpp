#include "modelindexiterator.h"

ModelIndexIterator::ModelIndexIterator(const QModelIndex &index)
    : index_(index)
{

}

QVariant ModelIndexIterator::dataAndNextColumn()
{
    QVariant data = index_.data();
    auto model = index_.model();
    index_ = model->index(index_.row(), index_.column()+1);

    return data;
}
