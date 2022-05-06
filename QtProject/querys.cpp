#include "querys.h"
#include "ui_querys.h"

Querys::Querys(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Querys)
{
    ui->setupUi(this);
}

Querys::~Querys()
{
    delete ui;
}

void Querys::on_query_1_button_clicked()
{
    ui->tableWidget = new QTableWidget(3, 3, this);

    for(int row=0; row!=ui->tableWidget->rowCount(); ++row){
        for(int column=0; column!=ui->tableWidget->columnCount(); ++column) {
            QTableWidgetItem *newItem = new QTableWidgetItem(tr("%1").arg((row+1)*(column+1)));
            ui->tableWidget->setItem(row, column, newItem);
        }
    }
}

