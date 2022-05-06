#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "viewwindow.h"
#include <connect.h>
#include <QMessageBox>
#include <QSqlDatabase>
#include <querywindow.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    hide();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_connect_triggered()
{
     Connect connect;
}


void MainWindow::on_querys_triggered()
{
    QueryWindow *window = new QueryWindow();
    window->show();
}

void MainWindow::on_edit_but_triggered()
{
    ViewWindow *window = new ViewWindow();
    window->setIsAdmin(getIsAdmin());
    window->show();
}

void MainWindow::on_button_auto_clicked()
{
    ui->lineEdit->show();
    ui->lineEdit_2->show();
    ui->label->show();
    ui->label_2->show();
    ui->log_butt->show();
}

void MainWindow::on_log_butt_clicked()
{

    QSqlQuery query;
    query.prepare("select authorization(:log,:pass)");
    query.bindValue(":log",ui->lineEdit->text());
    query.bindValue(":pass",ui->lineEdit_2->text());
    query.exec();
    query.next();
    if(query.value(0).toBool())
    {
        setIsAdmin(true);
        QMessageBox msgBox;
        msgBox.setText("Вы успешно перешли в режим администратора");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Неккоректный логин или пароль");
        msgBox.exec();
    }
    hide();
}

bool MainWindow::getIsAdmin() const
{
    return isAdmin;
}

void MainWindow::setIsAdmin(bool newIsAdmin)
{
    isAdmin = newIsAdmin;
}

void MainWindow::hide()
{
    ui->lineEdit->hide();
    ui->lineEdit_2->hide();
    ui->label->hide();
    ui->label_2->hide();
    ui->log_butt->hide();
}


void MainWindow::on_query_butt_clicked()
{
    QueryWindow *window = new QueryWindow();
    window->show();
}


void MainWindow::on_view_butt_clicked()
{
    ViewWindow *window = new ViewWindow();
    window->setIsAdmin(getIsAdmin());
    window->show();
}

