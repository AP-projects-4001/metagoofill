#ifndef PRODUCT_H
#define PRODUCT_H
#include <QMainWindow>
using namespace std;

class Product
{
public:
    Product();
    void string_to_char_array(string str, int len, char *array_char);
    void char_array_to_string(string &str, int len, char *array_char);

public:
    char type[16];
    int price;
    char berand[16];
    char color[16];
    int weight;
    int available;
    char descript[49];
    int ID;
    bool flag_berand;
    bool flag_color;
    bool flag_weight;
    bool flag_numerical;
    int ptr_file_myproduct_next;
    int ptr_file_myproduct_preview;
    int ptr_file_product_type_next;
    int ptr_file_product_type_preview;
    bool flag_delete_product;
    int ID_customer;
};

#endif // PRODUCT_H
