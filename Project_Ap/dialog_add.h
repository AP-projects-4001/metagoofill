#ifndef DIALOG_ADD_H
#define DIALOG_ADD_H

#include <QDialog>

namespace Ui {
class Dialog_add;
}

class Dialog_add : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_add(bool,bool,bool,bool,QWidget *parent = nullptr);
    ~Dialog_add();

private slots:

    void on_pushButton_cancel_clicked();

    void on_pushButton_confirm_clicked();

signals:

    void item_added2(QString,QString,QString,QString,QString,QString,QString,bool,bool,bool,bool);

private:
    Ui::Dialog_add *ui;
    bool flag_berand;
    bool flag_color;
    bool flag_weight;
    bool flag_numerical;
};

#endif // DIALOG_ADD_H
