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

private slots:
    void on_pushButton_4_clicked();

private:
    Ui::customerProf *ui;
};

#endif // CUSTOMERPROF_H



