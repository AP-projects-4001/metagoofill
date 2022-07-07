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

char customer::get_access(){
    return access;
}

int customer::get_ID(){
    return ID;
}

int customer::get_ptr_start_myproducts(){
    return ptr_start_myproducts;
}

int customer::get_ptr_start_mysells(){
    return ptr_start_mysells;
}

int customer::get_ptr_end_mysells(){
    return ptr_end_mysells;
}

int customer::get_number_myproducts(){
    return number_myproducts;
}

int customer::get_number_mysells(){
    return number_mysells;
}

int customer::get_Wallet_balance(){
    return Wallet_balance;
}

void customer::set_Name(char* _name){
    for(int i=0; i<16; i++)
    {
        Name[i] = _name[i];
    }
}

void customer::set_User(char* _user){
    for(int i=0; i<16; i++)
    {
        User[i] = _user[i];
    }
}

void customer::set_phoneNumber(char* _phonenumber){
    for(int i=0; i<12; i++)
    {
        PhoneNumber[i] = _phonenumber[i];
    }
}

void customer::set_Address(char* _address){
    for(int i=0; i<31; i++)
    {
        Address[i] = _address[i];
    }
}

void customer::set_Password(char* _password){
    for(int i=0; i<31; i++)
    {
        Password[i] = _password[i];
    }
}

void customer::set_city(char* _city){
    for(int i=0; i<11; i++)
    {
        city[i] = _city[i];
    }
}

void customer::set_ProductType(char _producttype){
    ProductType = _producttype;
}

void customer::set_access(char _access){
    access = _access;
}

void customer::set_ID(int id){
    ID = id;
}

void customer::set_ptr_start_myproducts(int _ptr_start_myproducts){
    ptr_start_myproducts = _ptr_start_myproducts;
}

void customer::set_ptr_start_mysells(int _ptr_start_mysells){
    ptr_start_mysells = _ptr_start_mysells;
}

void customer::set_ptr_end_mysells(int _ptr_end_mysells){
    ptr_end_mysells = _ptr_end_mysells;
}

void customer::set_number_myproducts(int _number_myproducts){
    number_myproducts = _number_myproducts;
}

void customer::set_number_mysells(int _number_mysells){
    number_mysells = _number_mysells;
}

void customer::set_Wallet_balance(int _Wallet_balance){
    Wallet_balance = _Wallet_balance;
}
