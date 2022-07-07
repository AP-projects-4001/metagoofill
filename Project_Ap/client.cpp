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

char client::get_access(){
    return access;
}

int client::get_ID(){
    return ID;
}

int client::get_ptr_start_mybuys(){
    return ptr_start_mybuys;
}

int client::get_ptr_end_mybuys(){
    return ptr_end_mybuys;
}

int client::get_number_mybuys(){
    return number_mybuys;
}

int client::get_Wallet_balance(){
    return Wallet_balance;
}

void client::set_Name(char* _name){
    for (int i=0; i<16; i++)
    {
        Name[i] = _name[i];
    }
}

void client::set_User(char* _user)
{
    for (int i=0; i<16; i++)
    {
        User[i] = _user[i];
    }
}

void client::set_phoneNumber(char* _phonenumber){
    for (int i=0; i<12; i++)
    {
        CellPhoneNumber[i] = _phonenumber[i];
    }
}

void client::set_Address(char* _address){
    for (int i=0; i<31; i++)
    {
        Address[i] = _address[i];
    }
}

void client::set_Password(char* _password){
    for (int i=0; i<31; i++)
    {
        Password[i] = _password[i];
    }
}

void client::set_city(char* _city){
    for (int i=0; i<11; i++)
    {
        city[i] = _city[i];
    }
}

void client::set_access(char _access){
    access = _access;
}

void client::set_ID(int _id){
    ID = _id;
}

void client::set_ptr_start_mybuys(int _ptr_start){
    ptr_start_mybuys = _ptr_start;
}

void client::set_ptr_end_mybuys(int _ptr_end){
    ptr_end_mybuys = _ptr_end;
}

void client::set_number_mybuys(int _number_mybuys){
    number_mybuys = _number_mybuys;
}

void client::set_Wallet_balance(int _wallet_balance){
    Wallet_balance = _wallet_balance;
}
