#ifndef INFOFCLIE_H
#define INFOFCLIE_H

#include <QDialog>
#include "client.h"

namespace Ui {
class infofclie;
}

class infofclie : public QDialog
{
    Q_OBJECT

public:
    explicit infofclie(client clie, QWidget *parent = nullptr);
    ~infofclie();

    void show_infofclie();

private slots:
    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::infofclie *ui;
    client clie;
};

#endif // INFOFCLIE_H
