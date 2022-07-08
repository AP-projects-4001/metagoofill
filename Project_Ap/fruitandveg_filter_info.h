#ifndef FRUITANDVEG_FILTER_INFO_H
#define FRUITANDVEG_FILTER_INFO_H

#include <iostream>
using namespace std;

class fruitandveg_filter_info
{
public:
    fruitandveg_filter_info();
    string get_name_prod();
    string get_price_from();
    string get_price_to();
    string get_customer_name();
    string get_color();

    void set_name_prod(string _name_prod);
    void set_price_from(string _price_from);
    void set_price_to(string _price_to);
    void set_customer_name(string _customer_name);
    void set_color(string _color);

public:
    string name_prod;
    string price_from;
    string price_to;
    string customer_name;
    string color;
};

#endif // FRUITANDVEG_FILTER_INFO_H
