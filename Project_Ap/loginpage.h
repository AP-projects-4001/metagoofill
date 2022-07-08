#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QMainWindow>
#include <QTimer>
QT_BEGIN_NAMESPACE
namespace Ui { class LoginPage; }
QT_END_NAMESPACE

class LoginPage : public QMainWindow
{
    Q_OBJECT

public:
    LoginPage(QWidget *parent = nullptr);
    ~LoginPage();

private slots:
    void on_pushButton_7_clicked();
    void myfunction();
    void on_pushButton_9_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::LoginPage *ui;
    QTimer *timer;
};
#endif // LOGINPAGE_H
