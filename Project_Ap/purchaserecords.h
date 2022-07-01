#ifndef PURCHASERECORDS_H
#define PURCHASERECORDS_H

#include <QDialog>

namespace Ui {
class PurchaseRecords;
}

class PurchaseRecords : public QDialog
{
    Q_OBJECT

public:
    explicit PurchaseRecords(QWidget *parent = nullptr);
    ~PurchaseRecords();

private:
    Ui::PurchaseRecords *ui;
};

#endif // PURCHASERECORDS_H
