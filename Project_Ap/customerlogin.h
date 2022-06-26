#ifndef CUSTOMERLOGIN_H
#define CUSTOMERLOGIN_H

#include <QDialog>

namespace Ui {
class CustomerLogin;
}


struct Customer
{
    char Name[16];
    char User[16];
    char PhoneNumber[12];
    char Address[31];
    char Password[31];
    char city[11];
    char ProductType;
};

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
};

#endif // CUSTOMERLOGIN_H
