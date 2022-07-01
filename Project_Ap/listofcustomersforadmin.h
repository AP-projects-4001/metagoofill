#ifndef LISTOFCUSTOMERSFORADMIN_H
#define LISTOFCUSTOMERSFORADMIN_H

#include <QDialog>
#include "customer.h"
namespace Ui {
class ListOfCustomersForAdmin;
}

class ListOfCustomersForAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit ListOfCustomersForAdmin(QWidget *parent = nullptr);
    ~ListOfCustomersForAdmin();

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::ListOfCustomersForAdmin *ui;
};

#endif // LISTOFCUSTOMERSFORADMIN_H
