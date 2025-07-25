#include "userl3model.h"

UserL3Model::UserL3Model(QObject *parent)
    : QAbstractTableModel{parent}
{


}

int UserL3Model::rowCount(const QModelIndex &) const {
    return users.count();
}

int UserL3Model::columnCount(const QModelIndex &) const {
    return 9;
}

QVariant UserL3Model::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return QVariant();

    const UserL3 &user = users.at(index.row());

    switch (index.column()) {
    case 0: return user.name;
    case 1: return user.email;
    case 2: return user.description;
    case 3: return user.birth_day.toString("yyyy-MM-dd");
    case 4: return user.prefered_salary;
    case 5: return QMetaEnum::fromType<UserL3::Sex>().valueToKey(user.sex);
    case 6: return QMetaEnum::fromType<UserL3::PersonalityType>().valueToKey(user.personality_type);
    case 7: return user.strengthsSum();
    case 8: return user.position;
    default: return QVariant();
    }
}

QVariant UserL3Model::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
        case 0: return "Name";
        case 1: return "Email";
        case 2: return "Description";
        case 3: return "Birth Day";
        case 4: return "Preferred Salary";
        case 5: return "Sex";
        case 6: return "Personality";
        case 7: return "Strengths Sum";
        case 8: return "Position";
        default: return QVariant();
        }
    }
    return QVariant();
}

void UserL3Model::addUser(UserL3 user){
    beginInsertRows(QModelIndex(), users.size(), users.size());
    users.append(user);
    endInsertRows();
}

void UserL3Model::deleteUser(int index){
    beginRemoveRows(QModelIndex(), users.size(), users.size());

    if(index >= users.size() || index < 0) return;

    users.removeAt(index);
    endRemoveRows();
}
