#ifndef PLAYERS_H
#define PLAYERS_H

#include <QString>
#include <QModelIndex>


class Players
{
public:
    Players();
    Players(int id,QString name,QString role,int fk_team,int salary,int goals);
    int getId() const;
    void setId(int newId);

    const QString &getName() const;
    void setName(const QString &newName);

    const QString &getRole() const;
    void setRole(const QString &newRole);

    int getSalary() const;
    void setSalary(int newSalary);

    int getGoals() const;
    void setGoals(int newGoals);

    int getFk_team() const;
    void setFk_team(int newFk_team);

private:
    int id;
    QString name;
    QString role;
    int salary;
    int goals;
    int fk_team;
};

class PlayersViewModel : public QAbstractListModel
{
public:
    PlayersViewModel(QObject *parent=nullptr);
    int rowCount(const QModelIndex &) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    void populate(QList<Players> *newValues);
    void append(Players value);
    void update(int idx, Players value);
    void deleteRow(int idx);
    void insertAt(int idx, Players value);
private:
    QList<Players> *values;
};


#endif // PLAYERS_H
