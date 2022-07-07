#include "product.h"
#include <string>
using namespace std;
Product::Product()
{

}
void Product::string_to_char_array(string str, int len, char *char_array)
{
    int i=0;
    for(i=0;i<len-1;i++){
        if(i==str.size()){
            break;
        }
        char_array[i]=str[i];
    }
    char_array[i]='\0';

}
void Product::char_array_to_string(string &str, int len, char *char_array)
{
    str="";
    int i=0;
    for(i=0;i<len-1;i++){
        if(char_array[i]=='\0'){
            break;
        }
        str+=char_array[i];
    }
}

char* Product::get_type(){
    return type;
}
int Product::get_price()
{
    return price;
}
char* Product::get_berand()
{
    return berand;
}
char* Product::get_color()
{
    return color;
}
int Product::get_weight()
{
    return weight;
}
int Product::get_available()
{
    return available;
}
char* Product::get_descript()
{
    return descript;
}
int Product::get_ID()
{
    return ID;
}
bool Product::get_flag_berand()
{
    return flag_berand;
}
bool Product::get_flag_color()
{
    return flag_color;
}
bool Product::get_flag_weight()
{
    return flag_weight;
}
bool Product::get_flag_numerical()
{
    return flag_numerical;
}
int Product::get_ptr_file_myproduct_next()
{
    return ptr_file_myproduct_next;
}
int Product::get_ptr_file_myproduct_preview()
{
    return ptr_file_myproduct_preview;
}
int Product::get_ptr_file_product_type_next()
{
    return ptr_file_product_type_next;
}
int Product::get_ptr_file_product_type_preview()
{
    return ptr_file_product_type_preview;
}
bool Product::get_flag_delete_product()
{
    return flag_delete_product;
}
int Product::get_ID_customer()
{
    return ID_customer;
}

void Product::set_type(char* _type)
{
    for(int i=0; i<16; i++)
    {
        type[i] = _type[i];
    }
}

void Product::set_price(int _price)
{
    price = _price;
}

void Product::set_berand(char* _brand)
{
    for(int i=0; i<16; i++)
    {
        berand[i] = _brand[i];
    }
}

void Product::set_color(char* _color)
{
    for(int i=0; i<16; i++)
    {
        color[i] = _color[i];
    }
}

void Product::set_weight(int _weight)
{
    weight = _weight;
}

void Product::set_available(int _available)
{
    available = _available;
}

void Product::set_descript(char* _descript)
{
    for(int i=0; i<49; i++)
    {
        descript[i] = _descript[i];
    }
}

void Product::set_ID(int _id)
{
    ID = _id;
}

void Product::set_flag_berand(bool _flag_berand)
{
    flag_berand = _flag_berand;
}

void Product::set_flag_color(bool _flag_color)
{
    flag_color = _flag_color;
}

void Product::set_flag_weight(bool _flag_weight)
{
    flag_weight = _flag_weight;
}

void Product::set_flag_numerical(bool _flag_num)
{
    flag_numerical = _flag_num;
}

void Product::set_ptr_file_myproduct_next(int _ptr_file_myproduct_next)
{
    ptr_file_myproduct_next = _ptr_file_myproduct_next;
}

void Product::set_ptr_file_myproduct_preview(int _ptr_file_myproduct_preview)
{
    ptr_file_myproduct_preview = _ptr_file_myproduct_preview;
}

void Product::set_ptr_file_product_type_next(int _ptr_file_product_type_next)
{
    ptr_file_product_type_next = _ptr_file_product_type_next;
}

void Product::set_ptr_file_product_type_preview(int _ptr_file_product_type_preview)
{
    ptr_file_product_type_preview = _ptr_file_product_type_preview;
}

void Product::set_flag_delete_product(bool _flag_del)
{
    flag_delete_product = _flag_del;
}

void Product::set_ID_customer(int _ID_cus)
{
    ID_customer = _ID_cus;
}
