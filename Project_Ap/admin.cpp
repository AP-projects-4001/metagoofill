#include "admin.h"

using namespace std;
Admin::Admin()
{

}
void Admin::string_to_char_array(string str, int len, char *char_array)
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
void Admin::char_array_to_string(string &str, int len, char *char_array)
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

int Admin::get_Wallet_balance()
{
    return Wallet_balance;
}

void Admin::set_Wallet_balance(int _Wallet_balance)
{
    Wallet_balance=_Wallet_balance;
}
