#include "querywindow.h"
#include "ui_querywindow.h"
#include <qsqlquery.h>

QueryWindow::QueryWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QueryWindow)
{
    ui->setupUi(this);
    ui->pushButton->setToolTip("Выводит игроков, чьё кол-во голов больше параметра 1 и зарплата больше средней среди футболистов");
    ui->pushButton_2_1->setToolTip("Выводит табличное представление с сортировкой по возрастанию");
    ui->pushButton_2_2->setToolTip("Выводит табличное представление с сортировкой по убыванию");
    ui->pushButton_3->setToolTip("Выводит список игроков, его команду, забивших хотя бы 1 гол, где id команды между 2 и 6 ");
    ui->pushButton_4->setToolTip("Суммарное количество денег игроков каждой из команд, где сумма больше параметра 1");
    ui->pushButton_5->setToolTip("Список команд, Где есть хоть один вратарь");
    ui->pushButton_6->setToolTip("Добавляет игроку, с id = параметру 1 сумму денег  = 2 параметру");
    ui->pushButton_7->setToolTip("Список футболистов команды с id = 1 параметру");
    ui->pushButton_8->setToolTip("Получить результат матча с id = 1 параметру");



}

void QueryWindow::query_1()
{
    QSqlQuery query;
    query.prepare("SELECT player_name,player_role,team_name,salary, "
"CASE player_role "
    "WHEN 'goalkeeper' THEN 150000 "
    "ELSE 70000 "
"END award "
"FROM players "
"INNER JOIN teams ON players.team=teams.team_id "
"WHERE total_goals>:goals and salary > (SELECT AVG(salary) FROM players)");

    query.bindValue(":goals",ui->lineEdit->text());
    query.exec();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(query.size());
    ui->tableWidget->setColumnCount(5);
    QStringList LIST;
    LIST << "PlayerName" << "Role" << "Team" <<"Salary" << "Award";
    ui->tableWidget->setHorizontalHeaderLabels(LIST);

    fillTable(query);

}

void QueryWindow::query_2(bool a)
{
    QSqlQuery query;
    if(a)
        query.exec("select * from view_calendare ORDER BY match_date ASC");
    else
        query.exec("select * from view_calendare ORDER BY match_date DESC");
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(query.size());
    ui->tableWidget->setColumnCount(3);
    QStringList LIST;
    LIST << "date"<<"team1"<<"team2";
    ui->tableWidget->setHorizontalHeaderLabels(LIST);

    fillTable(query);
}

void QueryWindow::query_3()
{

    QSqlQuery query;
    query.exec("SELECT *,(SELECT team_name FROM teams WHERE team=team_id) AS team_Name "
"FROM (SELECT * FROM players WHERE total_goals > 0) as players "
"WHERE team in (SELECT team_id from teams WHERE team_id BETWEEN 2 and 6)");
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(query.size());
    ui->tableWidget->setColumnCount(7);
    QStringList LIST;
    LIST << "player_id"<<"player_name"<<"player_role"<<"team"<<"salary"<<"TotalGoals"<<"team_name";
    ui->tableWidget->setHorizontalHeaderLabels(LIST);

    fillTable(query);


}

void QueryWindow::query_4()
{
    QSqlQuery query;
    query.prepare(""
"SELECT team_name, SUM(salary) as moneys "
"FROM players,teams "
"WHERE team_id=team  "
"GROUP BY team_name HAVING SUM(salary)>:bindMoney");
    query.bindValue(":bindMoney",ui->lineEdit->text());
    query.exec();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(query.size());
    ui->tableWidget->setColumnCount(2);
    QStringList LIST;
    LIST << "TeamName" <<"Moneys";
    ui->tableWidget->setHorizontalHeaderLabels(LIST);

    fillTable(query);


}

void QueryWindow::query_5()
{
    QSqlQuery query;
    query.exec(""
"SELECT team_name "
"FROM teams "
"WHERE team_id = ANY (SELECT team FROM players WHERE player_role='goalkeeper') ");
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(query.size());
    ui->tableWidget->setColumnCount(1);
    QStringList LIST;
    LIST << "TeamName";
    ui->tableWidget->setHorizontalHeaderLabels(LIST);

    fillTable(query);


}

void QueryWindow::fillTable(QSqlQuery query)
{
    for(int row=0; row!=ui->tableWidget->rowCount(); ++row)
    {
        query.next();
        for(int column=0; column!=ui->tableWidget->columnCount(); ++column)
        {
            QTableWidgetItem *newItem = new QTableWidgetItem(query.value(column).toString());
            ui->tableWidget->setItem(row, column, newItem);
        }
    }
}

QueryWindow::~QueryWindow()
{
    delete ui;
}

void QueryWindow::on_pushButton_clicked()
{
    query_1();
}


void QueryWindow::on_pushButton_3_clicked()
{
    query_3();
}


void QueryWindow::on_pushButton_4_clicked()
{
    query_4();
}


void QueryWindow::on_pushButton_5_clicked()
{
    query_5();
}


void QueryWindow::on_pushButton_2_1_clicked()
{
    query_2(true);
}


void QueryWindow::on_pushButton_2_2_clicked()
{
    query_2(false);
}


void QueryWindow::on_pushButton_6_clicked()
{
    QSqlQuery query;
    query.prepare("select cursor_addmoneys(:id,:money)");
    query.bindValue(":id",ui->lineEdit->text());
    query.bindValue(":money",ui->lineEdit_2->text());
    query.exec();
}


void QueryWindow::on_pushButton_7_clicked()
{
    QSqlQuery query;
    query.prepare("select get_players(:id)");
    query.bindValue(":id",ui->lineEdit->text());
    query.exec();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(query.size());
    ui->tableWidget->setColumnCount(1);
    QStringList LIST;
    LIST << "Name";
    ui->tableWidget->setHorizontalHeaderLabels(LIST);

    fillTable(query);
}




void QueryWindow::on_pushButton_8_clicked()
{
    QSqlQuery query;
    query.prepare("select get_result(:id)");
    query.bindValue(":id",ui->lineEdit->text());
    query.exec();
    ui->tableWidget->clear();
    ui->tableWidget->setRowCount(query.size());
    ui->tableWidget->setColumnCount(1);
    QStringList LIST;
    LIST << "result";
    ui->tableWidget->setHorizontalHeaderLabels(LIST);

    fillTable(query);
}

