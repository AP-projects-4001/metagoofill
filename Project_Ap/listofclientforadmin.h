#ifndef LISTOFCLIENTFORADMIN_H
#define LISTOFCLIENTFORADMIN_H

#include <QDialog>
#include "infofclie.h"

namespace Ui {
class ListOFClientForAdmin;
}

class ListOFClientForAdmin : public QDialog
{
    Q_OBJECT

public:
    explicit ListOFClientForAdmin(QWidget *parent = nullptr);
    ~ListOFClientForAdmin();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::ListOFClientForAdmin *ui;
    infofclie *clie_inf;
};

#endif // LISTOFCLIENTFORADMIN_H
