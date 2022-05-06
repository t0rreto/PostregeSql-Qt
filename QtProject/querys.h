#ifndef QUERYS_H
#define QUERYS_H

#include <QWidget>

namespace Ui {
class Querys;
}

class Querys : public QWidget
{
    Q_OBJECT

public:
    explicit Querys(QWidget *parent = nullptr);
    ~Querys();

private slots:
    void on_query_1_button_clicked();

private:
    Ui::Querys *ui;
};

#endif // QUERYS_H
