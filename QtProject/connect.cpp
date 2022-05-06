#include "connect.h"

#include <QMessageBox>
#include <QSqlDatabase>

Connect::Connect()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
    db.setDatabaseName("test1");
    db.setUserName("postgres");
    db.setHostName("localhost");
    db.setPassword("123");
    if (db.open())
    {
        QMessageBox msgBox;
        msgBox.setText("База Данных открыта");
        msgBox.exec();
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText("Ошибка подключения");
        msgBox.exec();
    }
}
