#include<stdio.h>
#include<string.h>
#include "HashMap.h"
#include "DataBase.h"
int main(void){
    DataBase DB = createDataBase(NULL,"123",true);
    DB->put(DB,"123","123","121323");
    printf("%s",(char*)DB->get(DB,"123","123"));
    return 0;
}