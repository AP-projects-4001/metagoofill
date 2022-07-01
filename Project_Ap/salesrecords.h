#ifndef SALESRECORDS_H
#define SALESRECORDS_H

#include <QDialog>

namespace Ui {
class SalesRecords;
}

class SalesRecords : public QDialog
{
    Q_OBJECT

public:
    explicit SalesRecords(QWidget *parent = nullptr);
    ~SalesRecords();

private:
    Ui::SalesRecords *ui;
};

#endif // SALESRECORDS_H
