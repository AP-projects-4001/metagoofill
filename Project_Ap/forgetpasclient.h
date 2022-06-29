#ifndef FORGETPASCLIENT_H
#define FORGETPASCLIENT_H

#include <QDialog>
#include "client.h"
namespace Ui {
class ForgetPasClient;
}

class ForgetPasClient : public QDialog
{
    Q_OBJECT

public:
    explicit ForgetPasClient(QWidget *parent = nullptr);
    ~ForgetPasClient();

private slots:
    void on_pushButton_2_clicked();
    void Getpas(QString);
    void on_pushButton_clicked();

private:
    Ui::ForgetPasClient *ui;
    class client cli_tmp;
};

#endif // FORGETPASCLIENT_H
