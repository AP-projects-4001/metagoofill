#ifndef ADMINPAGE_H
#define ADMINPAGE_H

#include <QDialog>
#include "listoftransactions.h"
#include "listofcustomersforadmin.h"
namespace Ui {
class AdminPage;
}

class AdminPage : public QDialog
{
    Q_OBJECT

public:
    explicit AdminPage(QWidget *parent = nullptr);
    ~AdminPage();

private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::AdminPage *ui;
};

#endif // ADMINPAGE_H
