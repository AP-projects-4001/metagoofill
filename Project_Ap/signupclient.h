#ifndef SIGNUPCLIENT_H
#define SIGNUPCLIENT_H
#include <QVector>
#include <QDialog>
#include "client.h"

namespace Ui {
class SignUpClient;
}

class SignUpClient : public QDialog
{
    Q_OBJECT


public:
    explicit SignUpClient(QWidget *parent = nullptr);
    ~SignUpClient();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::SignUpClient *ui;
    //QVector<client>client;
};

#endif // SIGNUPCLIENT_H
