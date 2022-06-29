#ifndef GOODDETAILS_H
#define GOODDETAILS_H

#include <QDialog>
#include "product.h"

namespace Ui {
class goodDetails;
}

class goodDetails : public QDialog
{
    Q_OBJECT

public:
    explicit goodDetails(Product _product, QWidget *parent = nullptr);
    ~goodDetails();

private slots:
    void on_pushButton_clicked();

private:
    Ui::goodDetails *ui;
    Product Prdct;
};

#endif // GOODDETAILS_H
