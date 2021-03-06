#ifndef CUSTOMERLOGIN_H
#define CUSTOMERLOGIN_H

#include <QDialog>
#include "customer.h"
#include "customerprof.h"

namespace Ui {
class CustomerLogin;
}

class CustomerLogin : public QDialog
{
    Q_OBJECT

public:
    explicit CustomerLogin(QWidget *parent = nullptr);
    ~CustomerLogin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::CustomerLogin *ui;
    customerProf *dia2;
};

#endif // CUSTOMERLOGIN_H
