#include "factor.h"

Factor::Factor()
{

}

int Factor::get_ptr_product()
{
    return ptr_product;
}

int Factor::get_number()
{
    return number;
}

int Factor::get_price()
{
    return price;
}

int Factor::get_type()
{
    return type;
}

int Factor::get_ID_customer()
{
    return ID_customer;
}

int Factor::get_ID_client()
{
    return ID_client;
}

void Factor::set_ptr_product(int _ptr_product)
{
    ptr_product = _ptr_product;
}

void Factor::set_number(int _number)
{
    number = _number;
}

void Factor::set_price(int _price)
{
    price = _price;
}
void Factor::set_type(int _type)
{
    type = _type;
}

void Factor::set_ID_customer(int _ID_customer)
{
    ID_customer = _ID_customer;
}

void Factor::set_ID_client(int _ID_client)
{
    ID_client = _ID_client;
}
