#ifndef LISTOFTRANSACTIONS_H
#define LISTOFTRANSACTIONS_H

#include <QDialog>

namespace Ui {
class listoftransactions;
}

class listoftransactions : public QDialog
{
    Q_OBJECT

public:
    explicit listoftransactions(QWidget *parent = nullptr);
    ~listoftransactions();

private slots:
    void on_pushButton_clicked();

private:
    Ui::listoftransactions *ui;
};

#endif // LISTOFTRANSACTIONS_H
