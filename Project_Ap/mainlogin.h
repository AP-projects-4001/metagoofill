#ifndef MAINLOGIN_H
#define MAINLOGIN_H

#include <QDialog>

namespace Ui {
class MainLogin;
}

class MainLogin : public QDialog
{
    Q_OBJECT

public:
    explicit MainLogin(QWidget *parent = nullptr);
    ~MainLogin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::MainLogin *ui;
};

#endif // MAINLOGIN_H
