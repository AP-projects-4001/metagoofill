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

private slots:
    void on_pushButton_4_clicked();

private:
    Ui::infofclie *ui;
    client clie_inf;
};

#endif // INFOFCLIE_H
