#ifndef VIEWWINDOW_H
#define VIEWWINDOW_H
#include <QMainWindow>
#include <QWidget>
#include <qsqlquery.h>

namespace Ui {
class ViewWindow;
}

class ViewWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit ViewWindow(QWidget *parent = nullptr);

    ~ViewWindow();
    QSqlQuery transquery;
    void fillComboBox();
    void hideAll();
    void clearAll();
    void transfer(QString sum,QString sender,QString getter);

    bool getIsAdmin() const;
    void setIsAdmin(bool newIsAdmin);

private slots:
    void on_actionPlayers_triggered();

    void on_actionTeams_triggered();

    void on_actionMatches_triggered();

    void on_actionGoals_triggered();

    void comboBox_triggered();

    void comboBox_2_triggered();

    void on_pushButton_add_clicked();


    void on_pushButton_delete_clicked();


    void on_pushButton_update_clicked();



    void on_actiontransfer_triggered();

    void on_actioncursor_triggered();

private:
    bool isAdmin=false;
    Ui::ViewWindow *ui;
};

#endif // VIEWWINDOW_H
