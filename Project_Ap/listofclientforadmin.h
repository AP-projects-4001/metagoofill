#ifndef LISTOFCLIENTFORADMIN_H
#define LISTOFCLIENTFORADMIN_H

#include <QDialog>

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

private:
    Ui::ListOFClientForAdmin *ui;
};

#endif // LISTOFCLIENTFORADMIN_H
