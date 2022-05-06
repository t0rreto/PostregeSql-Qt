#include "teams.h"

Teams::Teams()
{

}
Teams::Teams(int id,QString name,QDate  foundation_date,QString city)
{
    this->id=id;
    this->name=name;
    this->foundation_date=foundation_date;
    this->city=city;
}

int Teams::getId() const
{
    return id;
}

void Teams::setId(int newId)
{
    id = newId;
}

const QString &Teams::getName() const
{
    return name;
}

void Teams::setName(const QString &newName)
{
    name = newName;
}

const QDate &Teams::getFoundation_date() const
{
    return foundation_date;
}

void Teams::setFoundation_date(const QDate  &newFoundation_date)
{
    foundation_date = newFoundation_date;
}

const QString &Teams::getCity() const
{
    return city;
}

void Teams::setCity(const QString &newCity)
{
    city = newCity;
}



TeamsViewModel::TeamsViewModel(QObject *parent)
    :QAbstractListModel(parent)
{
    values = new QList<Teams>();
}

int TeamsViewModel::rowCount(const QModelIndex &) const
{
    return values->count();
}

int TeamsViewModel::columnCount(const QModelIndex &) const
{
    return 4;
}

QVariant TeamsViewModel::data( const QModelIndex &index, int role ) const
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
                        value = this->values->at(index.row()).getFoundation_date();
                        break;
                    }
                    case 3: {
                        value = this->values->at(index.row()).getCity();
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

void TeamsViewModel::populate(QList<Teams> *newValues)
{
    int idx = this->values->count();
    this->beginInsertRows(QModelIndex(), 1, idx);
        this->values = newValues;
    endInsertRows();
 }



//
void TeamsViewModel::append(Teams value)
{
    int newRow = this->values->count()+1;

    this->beginInsertRows(QModelIndex(), newRow, newRow);
        values->append(value);
    endInsertRows();
}

void TeamsViewModel::update(int idx, Teams value)
{
    (*this->values)[idx] = value;

    QModelIndex item_idx_s = this->index(idx,0);
    QModelIndex item_idx_e = this->index(idx,this->columnCount(QModelIndex()));

    emit this->dataChanged(item_idx_s ,item_idx_e );
}

void TeamsViewModel::deleteRow(int idx)
{
    this->beginRemoveRows(QModelIndex(), idx,idx);

        (*this->values).removeAt(idx);

    this->endRemoveRows();
}

void TeamsViewModel::insertAt(int idx, Teams value)
{

    int newRow = idx;

    this->beginInsertRows(QModelIndex(), newRow, newRow);

        values->insert(newRow,value);

    endInsertRows();
}

QVariant TeamsViewModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal) {
        switch (section) {
        case 0:
            return QString("id");
        case 1:
            return QString("name");
        case 2:
            return QString("foundation_date");
        case 3:
            return QString("city");


        }

    }
    return QVariant();
}
