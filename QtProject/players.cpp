#include "players.h"

Players::Players()
{

}
Players::Players(int id,QString name,QString role,int fk_team,int salary,int goals)
{
    this->id=id;
    this->name=name;
    this->role=role;
    this->salary=salary;
    this->goals=goals;
    this->fk_team=fk_team;
}

int Players::getId() const
{
    return id;
}

void Players::setId(int newId)
{
    id = newId;
}

const QString &Players::getName() const
{
    return name;
}

void Players::setName(const QString &newName)
{
    name = newName;
}

const QString &Players::getRole() const
{
    return role;
}

void Players::setRole(const QString &newRole)
{
    role = newRole;
}

int Players::getSalary() const
{
    return salary;
}

void Players::setSalary(int newSalary)
{
    salary = newSalary;
}

int Players::getGoals() const
{
    return goals;
}

void Players::setGoals(int newGoals)
{
    goals = newGoals;
}

int Players::getFk_team() const
{
    return fk_team;
}

void Players::setFk_team(int newFk_team)
{
    fk_team = newFk_team;
}


PlayersViewModel::PlayersViewModel(QObject *parent)
    :QAbstractListModel(parent)
{
    values = new QList<Players>();
}

int PlayersViewModel::rowCount(const QModelIndex &) const
{
    return values->count();
}

int PlayersViewModel::columnCount(const QModelIndex &) const
{
    return 6;
}

QVariant PlayersViewModel::data( const QModelIndex &index, int role ) const
{

    QVariant value;

        switch ( role )
        {
            case Qt::DisplayRole: //string
            {
                switch (index.column())
                {
                    case 0: {
                        value = this->values->at(index.row()).getId();
                        break;
                    }
                    case 1: {
                        value = this->values->at(index.row()).getName();
                        break;
                    }
                case 2: {
                    value = this->values->at(index.row()).getRole();
                    break;
                }
                case 3: {
                    value = this->values->at(index.row()).getFk_team();
                    break;
                }
                case 4: {
                    value = this->values->at(index.row()).getSalary();
                    break;
                }
                case 5: {
                    value = this->values->at(index.row()).getGoals();
                    break;
                }

                }
            }
            break;

            case Qt::UserRole: //data
            {
                value = this->values->at(index.row()).getId();
            }
            break;

            default:
                break;
        }

    return value;
}

void PlayersViewModel::populate(QList<Players> *newValues)
{
    int idx = this->values->count();
    this->beginInsertRows(QModelIndex(), 1, idx);
        this->values = newValues;
    endInsertRows();
 }



//
void PlayersViewModel::append(Players value)
{
    int newRow = this->values->count()+1;

    this->beginInsertRows(QModelIndex(), newRow, newRow);
        values->append(value);
    endInsertRows();
}

void PlayersViewModel::update(int idx, Players value)
{
    (*this->values)[idx] = value;

    QModelIndex item_idx_s = this->index(idx,0);
    QModelIndex item_idx_e = this->index(idx,this->columnCount(QModelIndex()));

    emit this->dataChanged(item_idx_s ,item_idx_e );
}

void PlayersViewModel::deleteRow(int idx)
{
    this->beginRemoveRows(QModelIndex(), idx,idx);

        (*this->values).removeAt(idx);

    this->endRemoveRows();
}

void PlayersViewModel::insertAt(int idx, Players value)
{

    int newRow = idx;

    this->beginInsertRows(QModelIndex(), newRow, newRow);

        values->insert(newRow,value);

    endInsertRows();
}

QVariant PlayersViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("id");
        case 1:
            return QString("name");
        case 2:
            return QString("role");
        case 3:
            return QString("team");
        case 4:
            return QString("salary");
        case 5:
            return QString("goals");

        }

    }
    return QVariant();
}
