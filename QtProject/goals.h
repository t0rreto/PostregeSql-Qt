#ifndef GOALS_H
#define GOALS_H


#include <QString>
#include <QModelIndex>


class Goals
{
public:
    Goals();
    Goals(int id,int fk_player,int fk_team,int fk_match,int time);


    int getId() const;
    void setId(int newId);

    int getFk_player() const;
    void setFk_player(int newFk_player);

    int getFk_team() const;
    void setFk_team(int newFk_team);

    int getFk_match() const;
    void setFk_match(int newFk_match);


    int getTime() const;
    void setTime(int newTime);

private:
    int id;
    int fk_player;
    int fk_team;
    int fk_match;
    int time;
};

class GoalsViewModel : public QAbstractListModel
{
public:
    GoalsViewModel(QObject *parent=nullptr);
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void populate(QList<Goals> *newValues);
    void append(Goals value);
    void update(int idx, Goals value);
    void deleteRow(int idx);
    void insertAt(int idx, Goals value);
private:
    QList<Goals> *values;
};


#endif // GOALS_H
