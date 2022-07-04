#ifndef CLIENT_H
#define CLIENT_H
#include <iostream>

class client
{
    //*important* we must change it to private!!!!!
public:
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



};

#endif // CLIENT_H
