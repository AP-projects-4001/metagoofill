#ifndef FORGETPASCUSTOMER_H
#define FORGETPASCUSTOMER_H

#include <QDialog>

namespace Ui {
class ForgetPasCustomer;
}

class ForgetPasCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit ForgetPasCustomer(QWidget *parent = nullptr);
    ~ForgetPasCustomer();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::ForgetPasCustomer *ui;
};

#endif // FORGETPASCUSTOMER_H
