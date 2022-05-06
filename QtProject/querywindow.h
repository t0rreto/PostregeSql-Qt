#ifndef QUERYWINDOW_H
#define QUERYWINDOW_H

#include <QMainWindow>
#include <qsqlquery.h>

namespace Ui {
class QueryWindow;
}

class QueryWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit QueryWindow(QWidget *parent = nullptr);
    ~QueryWindow();
    void fillTable(QSqlQuery query);
    void query_1();
    void query_2(bool a);
    void query_3();
    void query_4();
    void query_5();



private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_2_1_clicked();

    void on_pushButton_2_2_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::QueryWindow *ui;
};

#endif // QUERYWINDOW_H
