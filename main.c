#include<stdio.h>
#include<string.h>
#include "HashMap.h"
#include "DataBase.h"
int main(void){
    Table tab = createTable("1234",1);
    tab->put(tab,"21312","sadaf");
    printf("%s\n",tab->get(tab,"213132"));
    return 0;
}