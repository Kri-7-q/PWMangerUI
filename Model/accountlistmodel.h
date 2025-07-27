#ifndef ACCOUNTLISTMODEL_H
#define ACCOUNTLISTMODEL_H

#include <QAbstractItemModel>

class Private;
class QSqlRecord;

class AccountListModel : public QAbstractItemModel
{
    Q_OBJECT

public:
    explicit AccountListModel(QObject *parent = nullptr);
    ~AccountListModel();

    // Header:
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    // Basic functionality:
    QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const override;
    QModelIndex parent(const QModelIndex&) const override;

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    void setContent(QList<QSqlRecord>& list);

private:
    Private *d;
};

#endif // ACCOUNTLISTMODEL_H
