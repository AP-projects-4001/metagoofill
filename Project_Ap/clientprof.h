#ifndef CLIENTPROF_H
#define CLIENTPROF_H

#include <QMainWindow>
#include <fstream>
#include <cstring>
#include "client.h"


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

private:
    Ui::clientProf *ui;
    client clie;
};

#endif // CLIENTPROF_H
