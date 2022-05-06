#ifndef MATCHES_H
#define MATCHES_H

#include <QModelIndex>
#include <qdatetime.h>
#include <qstring.h>



class Matches
{
public:
    Matches();
    Matches(int id,int team1,int team2,QDate date,bool completed);




    int getId() const;
    void setId(int newId);

    int getTeam1() const;
    void setTeam1(int newTeam1);

    int getTeam2() const;
    void setTeam2(int newTeam2);

    const QDate &getDate() const;
    void setDate(const QDate &newDate);

    bool getCompleted() const;
    void setCompleted(bool newCompleted);

private:
    int id;
    int team1;
    int team2;
    QDate date;
    bool completed;
};

class MatchesViewModel : public QAbstractListModel
{
public:
    MatchesViewModel(QObject *parent=nullptr);
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void populate(QList<Matches> *newValues);
    void append(Matches value);
    void update(int idx, Matches value);
    void deleteRow(int idx);
    void insertAt(int idx, Matches value);
private:
    QList<Matches> *values;
};

#endif // MATCHES_H
