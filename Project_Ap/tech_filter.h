#ifndef TECH_FILTER_H
#define TECH_FILTER_H

#include <QDialog>
#include "others_filter_info.h"

namespace Ui {
class tech_filter;
}

class tech_filter : public QDialog
{
    Q_OBJECT

public:
    explicit tech_filter(QWidget *parent = nullptr);
    ~tech_filter();

signals:
    void send_tech_info(others_filter_info);

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::tech_filter *ui;
    others_filter_info tech_info;
};

#endif // TECH_FILTER_H
