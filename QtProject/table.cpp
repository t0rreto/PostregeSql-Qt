#include "table.h"

Players::Players()
{

}
Players::Players(int id,QString name,QString role,int salary,int goals,int fk_team)
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
