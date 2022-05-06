#ifndef TABLE_H
#define TABLE_H

#include <QString>
class Table{};

class Players
{
public:
    Players();

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


#endif // TABLES_H
