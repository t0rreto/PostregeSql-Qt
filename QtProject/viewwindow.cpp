#include "viewwindow.h"
#include "ui_viewwindow.h"
#include "players.h"
#include "teams.h"
#include "matches.h"
#include "goals.h"
#include "transactionwindow.h"

#include <qmessagebox.h>
#include <qsqlquery.h>

ViewWindow::ViewWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ViewWindow)
{
    ui->setupUi(this);
    hideAll();
    fillComboBox();
    comboBox_triggered();


}

ViewWindow::~ViewWindow()
{
    delete ui;
}

void ViewWindow::on_actionPlayers_triggered()
{
    PlayersViewModel *model = new PlayersViewModel();
    QList<Players> *list = new QList<Players>;
    QSqlQuery query;
    query.exec("SELECT * FROM players ORDER BY player_id ASC");
    while(query.next())
    {
        Players player = *new Players(query.value(0).toInt(),query.value(1).toString(),query.value(2).toString(),query.value(3).toInt(),query.value(4).toInt(),query.value(5).toInt());
        list->append(player);
    }
    model->populate(list);
    this->ui->tableView->setModel(model);
}

void ViewWindow::on_actionTeams_triggered()
{
    TeamsViewModel *model = new TeamsViewModel();
    QList<Teams> *list = new QList<Teams>;
    QSqlQuery query;
    query.exec("SELECT * FROM public.teams ORDER BY team_id ASC");
    while(query.next())
    {
        Teams team = *new Teams(query.value(0).toInt(),query.value(1).toString(),query.value(2).toDate(),query.value(3).toString());
        list->append(team);
    }
    model->populate(list);
    this->ui->tableView->setModel(model);}

void ViewWindow::on_actionMatches_triggered()
{
    MatchesViewModel *model = new MatchesViewModel();
    QList<Matches> *list = new QList<Matches>;
    QSqlQuery query;
    query.exec("SELECT * FROM public.matches ORDER BY match_id ASC");
    while(query.next())
    {
        Matches match = *new Matches(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toDate(),query.value(4).toBool());
        list->append(match);
    }
    model->populate(list);

    this->ui->tableView->setModel(model);
}

void ViewWindow::on_actionGoals_triggered()
{
    GoalsViewModel *model = new GoalsViewModel();
    QList<Goals> *list = new QList<Goals>;
    QSqlQuery query;
    query.exec("SELECT * FROM public.goals ORDER BY goal_id ASC");
    while(query.next())
    {
        Goals goals = *new Goals(query.value(0).toInt(),query.value(1).toInt(),query.value(2).toInt(),query.value(3).toInt(),query.value(4).toInt());
        list->append(goals);
    }
    model->populate(list);
    this->ui->tableView->setModel(model);
}

void ViewWindow::comboBox_triggered()
{
    QSqlQuery query;
    hideAll();
    clearAll();
    int  value = ui->comboBoxTeams->currentIndex();
    switch (value)
    {
        case 0://игрок
        {
            QString team;
            ui->lineEdit->show();
            ui->comboBox_2->show();
            ui->comboBox_3->show();
            ui->lineEdit_4->show();
            ui->label->setText("Имя игрока");
            ui->label_2->setText("Роль");
            ui->label_3->setText("Команда игрока");
            ui->label_4->setText("Зарплата");
            ui->label_5->setText("id *только при удаление/обновление*)");
            QStringList roles = {"defender", "striker", "goalkeeper","midfielder"};
            ui->comboBox_2->addItems(roles);
            query.exec("SELECT team_name,team_id FROM teams ORDER BY team_name ASC");
            while(query.next())
            {
                team = query.value(0).toString() + "  id: " + query.value(1).toString();
                ui->comboBox_3->addItem(team);
            }
            break;
        }
        case 1://команда
        {
            ui->dateEdit->show();
            ui->lineEdit_2->show();
            ui->lineEdit_3->show();
            ui->label->setText("Дата основания");
            ui->label_2->setText("Название команды");
            ui->label_3->setText("Город");
            ui->label_5->setText("id *только при удаление/обновление*)");
            break;
        }
        case 2://матч
        {
            QString team;
            ui->dateEdit->show();
            ui->comboBox_2->show();
            ui->comboBox_3->show();
            ui->comboBox_4->show();
            ui->label->setText("Дата матча");
            ui->label_2->setText("Команда 1");
            ui->label_3->setText("Команда 2");
            ui->label_4->setText("Состояние матча");
            ui->label_5->setText("id *только при удаление/обновление*)");
            query.exec("SELECT team_name,team_id FROM teams ORDER BY team_name ASC");
            while(query.next())
            {
                team = query.value(0).toString() + "  id: " + query.value(1).toString();
                ui->comboBox_2->addItem(team);
                ui->comboBox_3->addItem(team);
            }
            QStringList temp = {"Состоялся", "Еще не состоялся"};
            ui->comboBox_4->addItems(temp);

            break;
        }
        case 3://гол
        {
            ui->lineEdit->show();
            ui->comboBox_2->show();
            ui->lineEdit_3->show();
            ui->comboBox_4->show();

            ui->label->setText("Время гола (0-100 минута)");
            ui->label_2->setText("Игрок");
            ui->label_3->setText("Команда");
            ui->label_4->setText("Матч");
            ui->label_5->setText("id *только при удаление/обновление*)");
            query.exec("SELECT player_name,player_id FROM players ORDER BY player_name ASC");
            while(query.next())
            {
                ui->comboBox_2->addItem(query.value(0).toString()+"  id: "+query.value(1).toString());
            }
            ui->lineEdit_3->setReadOnly(true);

            break;
         }
    }
}

void ViewWindow::comboBox_2_triggered()
{

    int  value = ui->comboBoxTeams->currentIndex();
    if(value==3)
    {
        ui->comboBox_4->clear();
        QString player_id=ui->comboBox_2->currentText().split("  id: ")[1];
        QString team_name;
        QSqlQuery query;
        query.prepare("SELECT team_name,team_id FROM teams INNER JOIN players ON team=team_id WHERE player_id=:id");
        query.bindValue(":id",player_id);
        query.exec();
        while(query.next())
        {
            ui->lineEdit_3->setText(query.value(0).toString()+ " id: " + query.value(1).toString());
            team_name=query.value(0).toString();
        }
        query.prepare("SELECT t1.team_name,t2.team_name, match_date, match_id FROM matches"
        " INNER JOIN teams t1 ON (matches.team1 = t1.team_id) "
        " INNER JOIN teams t2 ON (matches.team2 = t2.team_id)"
        " WHERE t1.team_name = :team or t2.team_name = :team ORDER BY match_date ASC");
        query.bindValue(":team",team_name);
        query.exec();
        while(query.next())
        {
            QString temp = query.value(2).toString() + "\n" + query.value(0).toString() + " vs " + query.value(1).toString() + " id: " + query.value(3).toString();
            ui->comboBox_4->addItem(temp);
        }
    }
}

void ViewWindow::fillComboBox()
{
    QStringList tables = {"Игроки", "Команды", "Матчи", "Голы"};
    ui->comboBoxTeams->addItems(tables);
    connect(ui->comboBoxTeams, SIGNAL(activated(int)), this, SLOT(comboBox_triggered()));
    connect(ui->comboBox_2, SIGNAL(activated(int)), this, SLOT(comboBox_2_triggered()));
}

void ViewWindow::hideAll()
{
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->lineEdit_3->hide();
    ui->lineEdit_4->hide();
    ui->comboBox_2->hide();
    ui->comboBox_3->hide();
    ui->comboBox_4->hide();
    ui->dateEdit->hide();

}

void ViewWindow::clearAll()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
    ui->lineEdit_5->clear();
    ui->comboBox_2->clear();
    ui->comboBox_3->clear();
    ui->comboBox_4->clear();
    ui->lineEdit_3->setReadOnly(false);
    ui->label->clear();
    ui->label_2->clear();
    ui->label_3->clear();
    ui->label_4->clear();
    ui->label_5->clear();
}

void ViewWindow::on_pushButton_add_clicked()
{


    QSqlQuery query;
    int  value = ui->comboBoxTeams->currentIndex();
    switch (value)
    {
        case 0:
        {
            QString team_id = ui->comboBox_3->currentText().split("id: ")[1];

            query.prepare("SELECT add_players(:player_name, :player_role, :team, :salary)");
            query.bindValue(":player_name",ui->lineEdit->text());
            query.bindValue(":player_role",ui->comboBox_2->currentText());
            query.bindValue(":team",team_id);
            query.bindValue(":salary",ui->lineEdit_4->text());
            query.exec();

            break;
        }
        case 1:
        {
            query.prepare("SELECT add_teams(:team_name, :foundation_date, :city)");
            query.bindValue(":foundation_date",ui->dateEdit->date());
            query.bindValue(":team_name",ui->lineEdit_2->text());
            query.bindValue(":city",ui->lineEdit_3->text());
            query.exec();
            break;
        }
        case 2:
        {

            QString team1_id = ui->comboBox_2->currentText().split("id: ")[1];
            QString team2_id = ui->comboBox_3->currentText().split("id: ")[1];
            query.prepare("SELECT add_matches(:t1,:t2,:date,:compl)");
            query.bindValue(":t1",team1_id);
            query.bindValue(":t2",team2_id);
            query.bindValue(":date",ui->dateEdit->date());
            if(ui->comboBox_4->currentText()=="Состоялся") query.bindValue(":compl",true);
            else query.bindValue(":compl",false);
            query.exec();
            break;
        }
        case 3:
        {

            QString player_id = ui->comboBox_2->currentText().split("id: ")[1];
            QString team_id = ui->lineEdit_3->text().split("id: ")[1];
            QString match_id = ui->comboBox_4->currentText().split("id: ")[1];

            query.prepare("SELECT add_goals(:player,:team,:match,:time)");
            query.bindValue(":player",player_id);
            query.bindValue(":team",team_id);
            query.bindValue(":match",match_id);
            query.bindValue(":time",ui->lineEdit->text());
            query.exec();
            break;
        }

    }
     comboBox_triggered();
}

void ViewWindow::on_pushButton_delete_clicked()
{

    if(!getIsAdmin())
    {
        QMessageBox msgBox;
        msgBox.setText("Удаление данных может происходить в мастер режиме.");
        msgBox.exec();
        return;
    }
    QSqlQuery query;
    int  value = ui->comboBoxTeams->currentIndex();
    switch (value)
    {
        case 0:
        {
            query.prepare("SELECT remove_players(:id)");
            query.bindValue(":id",ui->lineEdit_5->text());
            query.exec();
            break;
        }
        case 1:
        {
            query.prepare("select remove_team(:id)");
            query.bindValue(":id",ui->lineEdit_5->text());
            query.exec();
            break;
        }
        case 2:
        {
            query.prepare("SELECT remove_matches(:id)");
            query.bindValue(":id",ui->lineEdit_5->text());
            query.exec();
            break;
        }
        case 3:
        {
            query.prepare("SELECT remove_goals(:id)");
            query.bindValue(":id",ui->lineEdit_5->text());
            query.exec();
            break;
        }
    }
    comboBox_triggered();
}

void ViewWindow::on_pushButton_update_clicked()
{

    QSqlQuery query;
    int  value = ui->comboBoxTeams->currentIndex();
    switch (value)
    {
        case 0:
        {
            query.prepare("SELECT update_players(:id,:player_name, :player_role,:salary)");
            query.bindValue(":id",ui->lineEdit_5->text());
            query.bindValue(":player_name",ui->lineEdit->text());
            query.bindValue(":player_role",ui->comboBox_2->currentText());
            query.bindValue(":salary",ui->lineEdit_4->text());
            query.exec();

            break;
        }
        case 1:
        {
            query.prepare("SELECT update_teams(:id,:team_name, :foundation_date, :city)");
            query.bindValue(":id",ui->lineEdit_5->text());
            query.bindValue(":foundation_date",ui->dateEdit->date());
            query.bindValue(":team_name",ui->lineEdit_2->text());
            query.bindValue(":city",ui->lineEdit_3->text());
            query.exec();
            break;
        }
        case 2:
        {
            query.prepare("SELECT team1,team2 FROM matches WHERE match_id=:id");
            query.bindValue(":id",ui->lineEdit_5->text());
            query.exec();
            query.next();
            QString oldteam1=query.value(0).toString();
            QString oldteam2=query.value(1).toString();

            QString team1_id = ui->comboBox_2->currentText().split("  id: ")[1];
            QString team2_id = ui->comboBox_3->currentText().split("  id: ")[1];
            query.prepare("SELECT update_matches(:id,:t1,:t2,:date,:compl)");
            query.bindValue(":id",ui->lineEdit_5->text());
            query.bindValue(":t1",team1_id);
            query.bindValue(":t2",team2_id);
            query.bindValue(":date",ui->dateEdit->date());
            if(ui->comboBox_4->currentText()=="Состоялся") query.bindValue(":compl",true);
            else query.bindValue(":compl",false);
            query.exec();

            if(!((oldteam1==team1_id  && oldteam2==team2_id) ||(oldteam1==team2_id  && oldteam2==team1_id)))
            {
                query.prepare("delete FROM goals WHERE goal_match=:id");
                query.bindValue(":id",ui->lineEdit_5->text());
                query.exec();
            }

            break;
        }
        case 3:
        {

            QString player_id = ui->comboBox_2->currentText().split("id: ")[1];
            QString team_id = ui->lineEdit_3->text().split("id: ")[1];
            QString match_id = ui->comboBox_4->currentText().split("id: ")[1];

            query.prepare("SELECT update_goals(:id,:time,:player,:team,:match)");
            query.bindValue(":id",ui->lineEdit_5->text());
            query.bindValue(":player",player_id);
            query.bindValue(":team",team_id);
            query.bindValue(":match",match_id);
            query.bindValue(":time",ui->lineEdit->text());
            query.exec();
            break;
        }
    }
    comboBox_triggered();
}

void ViewWindow::transfer(QString sum,QString sender,QString getter)
{
    transquery.exec("BEGIN");
    transquery.prepare("select transfer_money(:sender,:getter,:sum)");
    transquery.bindValue(":sender",sender);
    transquery.bindValue(":getter",getter);
    transquery.bindValue(":sum",sum);
    transquery.exec();
    transquery.next();
    if(transquery.value(0).toBool())
    {
        transquery.exec("COMMIT");
        QMessageBox msgBox;
        msgBox.setText("Транзакция одобрена");
        msgBox.exec();
    }
    else
    {
        transquery.exec("ROLLBACK");
        QMessageBox msgBox;
        msgBox.setText("Недостаточно средств, транзакция отменена");
        msgBox.exec();
    }
}

void ViewWindow::on_actiontransfer_triggered()
{
    transactionwindow *window = new transactionwindow(this);
    window->show();
}

bool ViewWindow::getIsAdmin() const
{
    return isAdmin;
}

void ViewWindow::setIsAdmin(bool newIsAdmin)
{
    isAdmin = newIsAdmin;
}




void ViewWindow::on_actioncursor_triggered()
{
    QSqlQuery query;
    query.prepare("select cursor_addmoneys(:id,:money)");
    query.bindValue(":id",ui->lineEdit->text());
    query.bindValue(":money",ui->lineEdit_2->text());
}

