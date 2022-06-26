#include "client.h"

client::client()
{

}

void client::string_to_char_array(char *array_char, int len, std::string str)
{
    int i=0;
    for(i=0;i<len-1;i++){
        if(str[i]=='\0'){
            break;
        }
        array_char[i]=str[i];
    }
    array_char[i]='\0';
}

void client::char_array_to_string(std::string &str, int len, char *array_char)
{
    str="";
    int i=0;
    for(i=0;i<len-1;i++){
        if(array_char[i]=='\0'){
            break;
        }
        str += array_char[i];
    }
}

char* client::get_Name()
{
    return Name;
}

char* client::get_User()
{
    return User;
}

char* client::get_phoneNumber()
{
    return CellPhoneNumber;
}

char* client::get_Address()
{
    return Address;
}

char* client::get_Password()
{
    return Password;
}

char* client::get_city()
{
    return city;
}
