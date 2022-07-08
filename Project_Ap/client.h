#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>

class client
{
    //*important* we must change it to private!!!!!
private:
    char Name[16];
    char User[16];
    char CellPhoneNumber[12];
    char Address[31];
    char Password[31];
    char city[11];
    char access;
    int ID;
    int ptr_start_mybuys;
    int ptr_end_mybuys;
    int number_mybuys;
    int Wallet_balance;

public:
    client();
    void string_to_char_array(char *array_char, int len, std::string str);
    void char_array_to_string(std::string &str, int len, char *array_char);
    char* get_Name();
    char* get_User();
    char* get_phoneNumber();
    char* get_Address();
    char* get_Password();
    char* get_city();
    char get_access();
    int get_ID();
    int get_ptr_start_mybuys();
    int get_ptr_end_mybuys();
    int get_number_mybuys();
    int get_Wallet_balance();
    void set_Name(char* _name);
    void set_User(char* _user);
    void set_phoneNumber(char* _phonenumber);
    void set_Address(char* _address);
    void set_Password(char* _password);
    void set_city(char* _city);
    void set_access(char _access);
    void set_ID(int _id);
    void set_ptr_start_mybuys(int _ptr_start);
    void set_ptr_end_mybuys(int _ptr_end);
    void set_number_mybuys(int _number_mybuys);
    void set_Wallet_balance(int _wallet_balance);





};

#endif // CLIENT_H
