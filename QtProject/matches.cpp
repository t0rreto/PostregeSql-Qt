#include "matches.h"

Matches::Matches()
{

}
Matches::Matches(int id,int team1,int team2,QDate date,bool completed)
{
    this->id=id;
    this->team1=team1;
    this->team2=team2;
    this->date=date;
    this->completed=completed;
}

int Matches::getId() const
{
    return id;
}

void Matches::setId(int newId)
{
    id = newId;
}

int Matches::getTeam1() const
{
    return team1;
}

void Matches::setTeam1(int newTeam1)
{
    team1 = newTeam1;
}

int Matches::getTeam2() const
{
    return team2;
}

void Matches::setTeam2(int newTeam2)
{
    team2 = newTeam2;
}

const QDate &Matches::getDate() const
{
    return date;
}

void Matches::setDate(const QDate &newDate)
{
    date = newDate;
}

bool Matches::getCompleted() const
{
    return completed;
}

void Matches::setCompleted(bool newCompleted)
{
    completed = newCompleted;
}



MatchesViewModel::MatchesViewModel(QObject *parent)
    :QAbstractListModel(parent)
{
    values = new QList<Matches>();
}

int MatchesViewModel::rowCount(const QModelIndex &) const
{
    return values->count();
}

int MatchesViewModel::columnCount(const QModelIndex &) const
{
    return 5;
}

QVariant MatchesViewModel::data( const QModelIndex &index, int role ) const
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
                        value = this->values->at(index.row()).getTeam1();
                        break;
                    }
                    case 2: {
                        value = this->values->at(index.row()).getTeam2();
                        break;
                    }
                    case 3: {
                        value = this->values->at(index.row()).getDate();
                        break;
                    }
                    case 4: {
                        value = this->values->at(index.row()).getCompleted();
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

void MatchesViewModel::populate(QList<Matches> *newValues)
{
    int idx = this->values->count();
    this->beginInsertRows(QModelIndex(), 1, idx);
        this->values = newValues;
    endInsertRows();
 }



//
void MatchesViewModel::append(Matches value)
{
    int newRow = this->values->count()+1;

    this->beginInsertRows(QModelIndex(), newRow, newRow);
        values->append(value);
    endInsertRows();
}

void MatchesViewModel::update(int idx, Matches value)
{
    (*this->values)[idx] = value;

    QModelIndex item_idx_s = this->index(idx,0);
    QModelIndex item_idx_e = this->index(idx,this->columnCount(QModelIndex()));

    emit this->dataChanged(item_idx_s ,item_idx_e );
}

void MatchesViewModel::deleteRow(int idx)
{
    this->beginRemoveRows(QModelIndex(), idx,idx);

        (*this->values).removeAt(idx);

    this->endRemoveRows();
}

void MatchesViewModel::insertAt(int idx, Matches value)
{

    int newRow = idx;

    this->beginInsertRows(QModelIndex(), newRow, newRow);

        values->insert(newRow,value);

    endInsertRows();
}

QVariant MatchesViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("id");
        case 1:
            return QString("team1");
        case 2:
            return QString("team2");
        case 3:
            return QString("match_date");
        case 4:
            return QString("completed");

        }

    }
    return QVariant();
}


