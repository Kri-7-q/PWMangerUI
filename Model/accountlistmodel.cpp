#include "accountlistmodel.h"

#include "SearchAccount/matchobject.h"
#include "Persistance/sqlpersistance.h"

#include <QSqlRecord>

class Private
{
public:
    QList<QSqlRecord> accountList_;
};

AccountListModel::AccountListModel(QObject *parent)
    : QAbstractItemModel(parent)
    , d(new Private)
{
}

AccountListModel::~AccountListModel()
{
    delete d;
}

QVariant AccountListModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    QVariant sectionName;
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return sectionName;
    switch (section) {
    case 0:
        sectionName = "Id";
        break;
    case 1:
        sectionName = "Provider";
        break;
    case 2:
        sectionName = "Username";
    default:
        break;
    }

    return sectionName;
}

QModelIndex AccountListModel::index(int row, int column, const QModelIndex &) const
{
    if (row < 0 || row >= d->accountList_.size())
        return {};
    if (column < 0 || column >= d->accountList_[row].count())
        return {};
    return createIndex(row, column);
}

QModelIndex AccountListModel::parent(const QModelIndex&) const
{
    return {};
}

int AccountListModel::rowCount(const QModelIndex &) const
{
    return d->accountList_.size();
}

int AccountListModel::columnCount(const QModelIndex &) const
{
    return 3;
}

QVariant AccountListModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    if (role == Qt::DisplayRole)
    {
        QString field = SqlPersistance::_fieldNames[static_cast<DBField>(index.column())];
        return d->accountList_[index.row()].value(field);
    }

    return {};
}

void AccountListModel::setContent(QList<QSqlRecord> &list)
{
    beginResetModel();
    d->accountList_ = list;
    endResetModel();
}

void AccountListModel::filterWithSortList(const SortList<MatchObject> &sortList)
{
    QList<QSqlRecord> tempList;
    auto it = sortList.begin();
    do
    {
        tempList << d->accountList_[it.data().index()];
    } while(it.next());
    beginResetModel();
    d->accountList_ = tempList;
    endResetModel();
}

