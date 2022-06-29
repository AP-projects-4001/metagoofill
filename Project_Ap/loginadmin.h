#ifndef LOGINADMIN_H
#define LOGINADMIN_H

#include <QDialog>
#include "adminpage.h"
namespace Ui {
class Loginadmin;
}

class Loginadmin : public QDialog
{
    Q_OBJECT

public:
    explicit Loginadmin(QWidget *parent = nullptr);
    ~Loginadmin();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::Loginadmin *ui;
};

#endif // LOGINADMIN_H
