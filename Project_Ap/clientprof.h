#ifndef CLIENTPROF_H
#define CLIENTPROF_H

#include <QMainWindow>
#include <fstream>
#include <cstring>
#include "client.h"
#include "goodslist.h"
#include "groupinggoods.h"

namespace Ui {
class clientProf;
}

class clientProf : public QMainWindow
{
    Q_OBJECT

public:
    explicit clientProf(client cli_info, QWidget *parent = nullptr);
    ~clientProf();

private slots:
    void on_pushButton_8_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_4_clicked();

    void showw();

private:
    Ui::clientProf *ui;
    goodsList *goodslist;
    groupingGoods *goodsGroup;
    client clie;
};

#endif // CLIENTPROF_H
