#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool getIsAdmin() const;
    void setIsAdmin(bool newIsAdmin);
    void hide();

private slots:

    void on_connect_triggered();

    void on_querys_triggered();

    void on_edit_but_triggered();

    void on_button_auto_clicked();

    void on_log_butt_clicked();

    void on_query_butt_clicked();

    void on_view_butt_clicked();

private:
    bool isAdmin=false;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
