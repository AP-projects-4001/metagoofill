#include "clothes_filter_info.h"

clothes_filter_info::clothes_filter_info()
{

}

string clothes_filter_info::get_name_prod()
{
    return name_prod;
}
string clothes_filter_info::get_price_from()
{
    return price_from;
}
string clothes_filter_info::get_price_to()
{
    return price_to;
}
string clothes_filter_info::get_customer_name()
{
    return customer_name;
}
string clothes_filter_info::get_size()
{
    return size;
}
string clothes_filter_info::get_age()
{
    return age;
}
string clothes_filter_info::get_sex()
{
    return sex;
}
string clothes_filter_info::get_grouping()
{
    return grouping;
}
string clothes_filter_info::get_color()
{
    return color;
}

void clothes_filter_info::set_name_prod(string _name_prod)
{
    name_prod = _name_prod;
}
void clothes_filter_info::set_price_from(string _price_from)
{
    price_from  = _price_from;
}
void clothes_filter_info::set_price_to(string _price_to)
{
    price_to = _price_to;
}
void clothes_filter_info::set_customer_name(string _customer_name)
{
    customer_name = _customer_name;
}
void clothes_filter_info::set_size(string _size)
{
    size = _size;
}
void clothes_filter_info::set_age(string _age)
{
    age = _age;
}
void clothes_filter_info::set_sex(string _sex)
{
    sex = _sex;
}
void clothes_filter_info::set_grouping(string _grouping)
{
    grouping = _grouping;
}
void clothes_filter_info::set_color(string _color)
{
    color = _color;
}
