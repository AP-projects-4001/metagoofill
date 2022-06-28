#ifndef CLOTHES_FILTER_H
#define CLOTHES_FILTER_H

#include <QDialog>
#include "clothes_filter_info.h"

namespace Ui {
class clothes_filter;
}

class clothes_filter : public QDialog
{
    Q_OBJECT

public:
    explicit clothes_filter(QWidget *parent = nullptr);
    ~clothes_filter();

private slots:
    void on_pushButton_2_clicked();

signals:
    void send_clothes_info(clothes_filter_info);

private:
    Ui::clothes_filter *ui;
    clothes_filter_info clothes_info;
};

#endif // CLOTHES_FILTER_H
