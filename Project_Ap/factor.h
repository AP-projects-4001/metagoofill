#ifndef FACTOR_H
#define FACTOR_H


class Factor
{
public:
    Factor();
    int get_ptr_product();
    int get_number();
    int get_price();
    int get_type();
    int get_ID_customer();
    int get_ID_client();
    void set_ptr_product(int _ptr_product);
    void set_number(int _number);
    void set_price(int _price);
    void set_type(int _type);
    void set_ID_customer(int _ID_customer);
    void set_ID_client(int _ID_client);

public:
    int ptr_product;
    int number;
    int price;
    int type;
    int ID_customer;
    int ID_client;
};

#endif // FACTOR_H
