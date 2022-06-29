#ifndef RECOVERYPASCLIENT_H
#define RECOVERYPASCLIENT_H

#include <QDialog>

namespace Ui {
class RecoveryPasClient;
}

class RecoveryPasClient : public QDialog
{
    Q_OBJECT

public:
    explicit RecoveryPasClient(QWidget *parent = nullptr);
    ~RecoveryPasClient();
signals:
    void passPas(QString);
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::RecoveryPasClient *ui;
};

#endif // RECOVERYPASCLIENT_H
