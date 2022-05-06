#ifndef TEAMS_H
#define TEAMS_H


#include <QString>
#include <QModelIndex>
#include <QDate>


class Teams
{
public:
    Teams();
    Teams(int id,QString name,QDate  foundation_date,QString city);


    int getId() const;
    void setId(int newId);

    const QString &getName() const;
    void setName(const QString &newName);

    const QDate  &getFoundation_date() const;
    void setFoundation_date(const QDate  &newFoundation_date);

    const QString &getCity() const;
    void setCity(const QString &newCity);

private:
    int id;
    QString name;
    QDate foundation_date;
    QString city;
};

class TeamsViewModel : public QAbstractListModel
{
public:
    TeamsViewModel(QObject *parent=nullptr);
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void populate(QList<Teams> *newValues);
    void append(Teams value);
    void update(int idx, Teams value);
    void deleteRow(int idx);
    void insertAt(int idx, Teams value);
private:
    QList<Teams> *values;
};


#endif // TEAMS_H
