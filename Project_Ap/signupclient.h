#ifndef SIGNUPCLIENT_H
#define SIGNUPCLIENT_H
#include <QVector>
#include <QDialog>
namespace Ui {
class SignUpClient;
}

class SignUpClient : public QDialog
{
    Q_OBJECT
struct Client
{
      char Name[16];
      char User[16];
      char CellPhoneNumber[12];
      char Address[31];
      char Password[31];
      char city[11];
};
public:
    explicit SignUpClient(QWidget *parent = nullptr);
    ~SignUpClient();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::SignUpClient *ui;
    QVector<Client>client;
};

#endif // SIGNUPCLIENT_H
