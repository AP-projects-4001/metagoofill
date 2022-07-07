#ifndef ADMIN_H
#define ADMIN_H
#include <string>
using namespace std;
class Admin
{
public:
    int Wallet_balance;
    char User[16];
    char Password[31];
public:
    Admin();
    void string_to_char_array(string , int , char*);
    void char_array_to_string(string&, int, char*);
};

#endif // ADMIN_H
