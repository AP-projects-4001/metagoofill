#ifndef LOGINCLIENT_H
#define LOGINCLIENT_H
#include <QDialog>
#include "client.h"

//struct client{
//    char Name[16];
//    char User[16];
//    char CellPhoneNumber[12];
//    char Address[31];
//    char Password[31];
//    char city[11];
//};

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
};

#endif // LOGINCLIENT_H
