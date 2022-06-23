#ifndef RECOVERYPASCUSTOMER_H
#define RECOVERYPASCUSTOMER_H

#include <QDialog>

namespace Ui {
class RecoveryPasCustomer;
}

class RecoveryPasCustomer : public QDialog
{
    Q_OBJECT

public:
    explicit RecoveryPasCustomer(QWidget *parent = nullptr);
    ~RecoveryPasCustomer();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::RecoveryPasCustomer *ui;
};

#endif // RECOVERYPASCUSTOMER_H
