#ifndef HOMEAPPS_FILTER_H
#define HOMEAPPS_FILTER_H

#include <QDialog>
#include "others_filter_info.h"

namespace Ui {
class homeApps_filter;
}

class homeApps_filter : public QDialog
{
    Q_OBJECT

public:
    explicit homeApps_filter(QWidget *parent = nullptr);
    ~homeApps_filter();

signals:
    void send_homeapp_info(others_filter_info);

private slots:
    void on_pushButton_2_clicked();

private:
    Ui::homeApps_filter *ui;
    others_filter_info homeapp_info;
};

#endif // HOMEAPPS_FILTER_H
