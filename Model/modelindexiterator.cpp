#include "modelindexiterator.h"
#include "Model/accountlistmodel.h"

ModelIndexIterator::ModelIndexIterator(const QModelIndex &index)
    : index_(index)
{

}

QVariant ModelIndexIterator::data(DBField field)
{
    QModelIndex i = index_.model()->index(index_.row(), static_cast<int>(field));

    return i.data();
}

void ModelIndexIterator::setData(DBField field, QVariant &val)
{
    auto model = static_cast<AccountListModel*>(const_cast<QAbstractItemModel*>(index_.model()));
    QModelIndex index = model->index(index_.row(), static_cast<int>(field));
    model->setData(index, val, Qt::DisplayRole);
}

bool ModelIndexIterator::nextRow()
{
    auto model = index_.model();
    index_ = model->index(index_.row()+1, index_.column());

    return index_.isValid();
}
