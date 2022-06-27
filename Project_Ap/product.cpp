#include "product.h"
#include <string>
using namespace std;
Product::Product()
{

}
void Product::string_to_char_array(string str, int len, char *char_array)
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
void Product::char_array_to_string(string &str, int len, char *char_array)
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
