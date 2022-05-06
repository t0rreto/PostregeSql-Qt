#include "transactionwindow.h"
#include "ui_transactionwindow.h"
#include "viewwindow.h"

#include <QSqlQuery>

transactionwindow::transactionwindow(ViewWindow *parent) :
    QMainWindow(parent),
    ui(new Ui::transactionwindow)
{
    ui->setupUi(this);
    QSqlQuery query;
    this->parent=parent;
    query.exec("SELECT player_name,player_id FROM players ORDER BY player_name ASC");
    while(query.next())
    {
        ui->comboBox->addItem(query.value(0).toString()+"  id: "+query.value(1).toString());
        ui->comboBox_2->addItem(query.value(0).toString()+"  id: "+query.value(1).toString());
    }

}

transactionwindow::~transactionwindow()
{
    delete ui;
}

void transactionwindow::on_pushButton_clicked()
{
    QString sender_id = ui->comboBox->currentText().split("id: ")[1];
    QString getter_id = ui->comboBox_2->currentText().split("id: ")[1];
    QString sum = ui->lineEdit->text();
    parent->transfer(sum,sender_id,getter_id);
    this->close();
}

