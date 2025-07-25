#ifndef USERL3MODEL_H
#define USERL3MODEL_H

#include <QAbstractTableModel>
#include "userl3.h"


class UserL3Model : public QAbstractTableModel
{
private:
    QList<UserL3> users;

public:
    explicit UserL3Model(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const override;

    void addUser(UserL3 user);
    void deleteUser(int index);
};

#endif // USERL3MODEL_H
