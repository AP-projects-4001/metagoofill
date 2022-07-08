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
    char* get_type();
    int get_price();
    char* get_berand();
    char* get_color();
    int get_weight();
    int get_available();
    char* get_descript();
    int get_ID();
    bool get_flag_berand();
    bool get_flag_color();
    bool get_flag_weight();
    bool get_flag_numerical();
    int get_ptr_file_myproduct_next();
    int get_ptr_file_myproduct_preview();
    int get_ptr_file_product_type_next();
    int get_ptr_file_product_type_preview();
    bool get_flag_delete_product();
    int get_ID_customer();
    void set_type(char* _type);
    void set_price(int _price);
    void set_berand(char* _brand);
    void set_color(char* _color);
    void set_weight(int _weight);
    void set_available(int _available);
    void set_descript(char* _descript);
    void set_ID(int _id);
    void set_flag_berand(bool _flag_berand);
    void set_flag_color(bool _flag_color);
    void set_flag_weight(bool _flag_weight);
    void set_flag_numerical(bool _flag_num);
    void set_ptr_file_myproduct_next(int _ptr_file_myproduct_next);
    void set_ptr_file_myproduct_preview(int _ptr_file_myproduct_preview);
    void set_ptr_file_product_type_next(int _ptr_file_product_type_next);
    void set_ptr_file_product_type_preview(int _ptr_file_product_type_preview);
    void set_flag_delete_product(bool _flag_del);
    void set_ID_customer(int _ID_cus);

private:
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
