#ifndef CUSTOMERPROF_H
#define CUSTOMERPROF_H

#include <QMainWindow>
#include "customer.h"

namespace Ui {
class customerProf;
}

class customerProf : public QMainWindow
{
    Q_OBJECT

public:
    explicit customerProf(customer cus_info, QWidget *parent = nullptr);
    ~customerProf();

    void show_prof();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_5_clicked();

private:
    customer cust;
    Ui::customerProf *ui;
};

#endif // CUSTOMERPROF_H



