#include "goals.h"

Goals::Goals()
{

}
Goals::Goals(int id,int fk_player,int fk_team,int fk_match,int time)
{
    this->id=id;
    this->fk_player=fk_player;
    this->fk_team=fk_team;
    this->fk_match=fk_match;
    this->time=time;

}

int Goals::getId() const
{
    return id;
}

void Goals::setId(int newId)
{
    id = newId;
}

int Goals::getFk_player() const
{
    return fk_player;
}

void Goals::setFk_player(int newFk_player)
{
    fk_player = newFk_player;
}

int Goals::getFk_team() const
{
    return fk_team;
}

void Goals::setFk_team(int newFk_team)
{
    fk_team = newFk_team;
}

int Goals::getFk_match() const
{
    return fk_match;
}

void Goals::setFk_match(int newFk_match)
{
    fk_match = newFk_match;
}

int Goals::getTime() const
{
    return time;
}

void Goals::setTime(int newTime)
{
    time = newTime;
}






GoalsViewModel::GoalsViewModel(QObject *parent)
    :QAbstractListModel(parent)
{
    values = new QList<Goals>();
}

int GoalsViewModel::rowCount(const QModelIndex &) const
{
    return values->count();
}

int GoalsViewModel::columnCount(const QModelIndex &) const
{
    return 5;
}

QVariant GoalsViewModel::data( const QModelIndex &index, int role ) const
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
                        value = this->values->at(index.row()).getFk_player();
                        break;
                    }
                    case 2: {
                        value = this->values->at(index.row()).getFk_team();
                        break;
                    }
                    case 3: {
                        value = this->values->at(index.row()).getFk_match();
                        break;
                    }
                    case 4: {
                        value = this->values->at(index.row()).getTime();
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

void GoalsViewModel::populate(QList<Goals> *newValues)
{
    int idx = this->values->count();
    this->beginInsertRows(QModelIndex(), 1, idx);
        this->values = newValues;
    endInsertRows();
 }



//
void GoalsViewModel::append(Goals value)
{
    int newRow = this->values->count()+1;

    this->beginInsertRows(QModelIndex(), newRow, newRow);
        values->append(value);
    endInsertRows();
}

void GoalsViewModel::update(int idx, Goals value)
{
    (*this->values)[idx] = value;

    QModelIndex item_idx_s = this->index(idx,0);
    QModelIndex item_idx_e = this->index(idx,this->columnCount(QModelIndex()));

    emit this->dataChanged(item_idx_s ,item_idx_e );
}

void GoalsViewModel::deleteRow(int idx)
{
    this->beginRemoveRows(QModelIndex(), idx,idx);

        (*this->values).removeAt(idx);

    this->endRemoveRows();
}

void GoalsViewModel::insertAt(int idx, Goals value)
{

    int newRow = idx;

    this->beginInsertRows(QModelIndex(), newRow, newRow);

        values->insert(newRow,value);

    endInsertRows();
}

QVariant GoalsViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("id");
        case 1:
            return QString("fk_player");
        case 2:
            return QString("fk_team");
        case 3:
            return QString("fk_match");
        case 4:
            return QString("time");


        }

    }
    return QVariant();
}
