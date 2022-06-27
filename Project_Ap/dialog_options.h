#ifndef DIALOG_OPTIONS_H
#define DIALOG_OPTIONS_H

#include <QDialog>

namespace Ui {
class Dialog_options;
}

class Dialog_options : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_options(QWidget *parent = nullptr);
    ~Dialog_options();

private slots:
    void on_buttonBox_accepted();

signals:
    void item_added(bool,bool,bool,bool);

private:
    Ui::Dialog_options *ui;
};

#endif // DIALOG_OPTIONS_H
