#ifndef LOGINCLIENT_H
#define LOGINCLIENT_H
#include <QDialog>
#include "client.h"
#include "clientprof.h"

namespace Ui {
class LoginClient;
}

class LoginClient : public QDialog
{
    Q_OBJECT

public:
    explicit LoginClient(QWidget *parent = nullptr);
    ~LoginClient();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::LoginClient *ui;
    clientProf *dia2;
};

#endif // LOGINCLIENT_H
