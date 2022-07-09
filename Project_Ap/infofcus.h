#ifndef INFOFCUS_H
#define INFOFCUS_H

#include <QDialog>
#include "customer.h"

namespace Ui {
class infofcus;
}

class infofcus : public QDialog
{
    Q_OBJECT

public:
    explicit infofcus(customer cus, QWidget *parent = nullptr);
    ~infofcus();

    void show_infofcus();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::infofcus *ui;
    customer cust;
};

#endif // INFOFCUS_H
