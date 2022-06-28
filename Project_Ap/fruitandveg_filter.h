#ifndef FRUITANDVEG_FILTER_H
#define FRUITANDVEG_FILTER_H

#include <QDialog>
#include "fruitandveg_filter_info.h"

namespace Ui {
class fruitandveg_filter;
}

class fruitandveg_filter : public QDialog
{
    Q_OBJECT

public:
    explicit fruitandveg_filter(QWidget *parent = nullptr);
    ~fruitandveg_filter();

private slots:
    void on_pushButton_2_clicked();

signals:
    void send_fruits_info(fruitandveg_filter_info);

private:
    Ui::fruitandveg_filter *ui;
    fruitandveg_filter_info fruit_info;
};

#endif // FRUITANDVEG_FILTER_H
