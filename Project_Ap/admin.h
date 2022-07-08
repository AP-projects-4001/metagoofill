#ifndef ADMIN_H
#define ADMIN_H
#include <string>
using namespace std;
class Admin
{
private:
    int Wallet_balance;
    char User[16];
    char Password[31];
public:
    Admin();
    void string_to_char_array(string , int , char*);
    void char_array_to_string(string&, int, char*);
    char* get_User();
    char* get_Password();
    int get_Wallet_balance();
    void set_User(char* _user);
    void set_Password(char* _password);
    void set_Wallet_balance(int _Wallet_balance);
};

#endif // ADMIN_H
