#ifndef CART_H
#define CART_H

#include <QDialog>

namespace Ui {
class cart;
}

class cart : public QDialog
{
    Q_OBJECT

public:
    explicit cart(QWidget *parent = nullptr);
    ~cart();

private:
    Ui::cart *ui;
};

#endif // CART_H
