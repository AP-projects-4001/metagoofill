#include "fruitandveg_filter_info.h"

fruitandveg_filter_info::fruitandveg_filter_info()
{

}

string fruitandveg_filter_info::get_name_prod()
{
    return name_prod;
}
string fruitandveg_filter_info::get_price_from()
{
    return price_from;
}
string fruitandveg_filter_info::get_price_to()
{
    return price_to;
}
string fruitandveg_filter_info::get_customer_name()
{
    return customer_name;
}
string fruitandveg_filter_info::get_color()
{
    return color;
}

void fruitandveg_filter_info::set_name_prod(string _name_prod)
{
    name_prod = _name_prod;
}
void fruitandveg_filter_info::set_price_from(string _price_from)
{
    price_from = _price_from;
}
void fruitandveg_filter_info::set_price_to(string _price_to)
{
    price_to = _price_to;
}
void fruitandveg_filter_info::set_customer_name(string _customer_name)
{
    customer_name = _customer_name;
}
void fruitandveg_filter_info::set_color(string _color)
{
    color = _color;
}
