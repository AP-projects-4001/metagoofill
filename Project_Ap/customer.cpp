#include "customer.h"

customer::customer()
{

}

void customer::string_to_char_array(char *array_char, int len, std::string str)
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

void customer::char_array_to_string(std::string &str, int len, char *array_char)
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

char* customer::get_Name()
{
    return Name;
}

char* customer::get_User()
{
    return User;
}

char* customer::get_phoneNumber()
{
    return PhoneNumber;
}

char* customer::get_Address()
{
    return Address;
}

char* customer::get_Password()
{
    return Password;
}

char* customer::get_city()
{
    return city;
}
