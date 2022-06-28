#ifndef SUPER_FILTER_H
#define SUPER_FILTER_H

#include <QDialog>
#include "others_filter_info.h"

namespace Ui {
class super_filter;
}

class super_filter : public QDialog
{
    Q_OBJECT

public:
    explicit super_filter(QWidget *parent = nullptr);
    ~super_filter();

signals:
    void send_super_info(others_filter_info);

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::super_filter *ui;
    others_filter_info super_info;
};

#endif // SUPER_FILTER_H
