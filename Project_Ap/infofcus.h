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

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::infofcus *ui;
    customer cus_info;
};

#endif // INFOFCUS_H
