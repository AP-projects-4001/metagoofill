#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <iostream>

class customer
{
public:
    char Name[16];
    char User[16];
    char PhoneNumber[12];
    char Address[31];
    char Password[31];
    char city[11];
    char ProductType;
    char access;
    int ID;
    int ptr_start_myproducts;
    int ptr_start_mysells;
    int ptr_end_mysells;
    int number_myproducts;
    int number_mysells;
    int Wallet_balance;


public:
    customer();
    void string_to_char_array(char *array_char, int len, std::string str);
    void char_array_to_string(std::string &str, int len, char *array_char);
    char* get_Name();
    char* get_User();
    char* get_phoneNumber();
    char* get_Address();
    char* get_Password();
    char* get_city();
    char get_ProductType();
    char get_access();
    int get_ID();
    int get_ptr_start_myproducts();
    int get_ptr_start_mysells();
    int get_ptr_end_mysells();
    int get_number_myproducts();
    int get_number_mysells();
    int get_Wallet_balance();
    void set_Name(char* _name);
    void set_User(char* _user);
    void set_phoneNumber(char* _phonenumber);
    void set_Address(char* _address);
    void set_Password(char* _password);
    void set_city(char* _city);
    void set_ProductType(char _producttype);
    void set_access(char _access);
    void set_ID(int id);
    void set_ptr_start_myproducts(int _ptr_start_myproducts);
    void set_ptr_start_mysells(int _ptr_start_mysells);
    void set_ptr_end_mysells(int _ptr_end_mysells);
    void set_number_myproducts(int _number_myproducts);
    void set_number_mysells(int _number_mysells);
    void set_Wallet_balance(int _Wallet_balance);
};

#endif // CUSTOMER_H
