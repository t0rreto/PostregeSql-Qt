#ifndef TRANSACTIONWINDOW_H
#define TRANSACTIONWINDOW_H

#include "viewwindow.h"

#include <QWidget>

namespace Ui {
class transactionwindow;
}

class transactionwindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit transactionwindow(ViewWindow *parent);
    ~transactionwindow();
    ViewWindow *parent;

private slots:
    void on_pushButton_clicked();

private:
    Ui::transactionwindow *ui;
};

#endif // TRANSACTIONWINDOW_H
