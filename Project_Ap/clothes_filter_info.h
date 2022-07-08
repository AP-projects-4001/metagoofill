#ifndef CLOTHES_FILTER_INFO_H
#define CLOTHES_FILTER_INFO_H
#include <iostream>
using namespace std;

class clothes_filter_info
{
public:
    clothes_filter_info();
    string get_name_prod();
    string get_price_from();
    string get_price_to();
    string get_customer_name();
    string get_size();
    string get_age();
    string get_sex();
    string get_grouping();
    string get_color();

    void set_name_prod(string _name_prod);
    void set_price_from(string _price_from);
    void set_price_to(string _price_to);
    void set_customer_name(string _customer_name);
    void set_size(string _size);
    void set_age(string _age);
    void set_sex(string _sex);
    void set_grouping(string _grouping);
    void set_color(string _color);

public:
    string name_prod;
    string price_from;
    string price_to;
    string customer_name;
    string size;
    string age;
    string sex;
    string grouping;
    string color;
};

#endif // CLOTHES_FILTER_INFO_H
