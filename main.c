#include<stdio.h>
#include<string.h>
#include "HashMap.h"
#include "DataBase.h"
int main(void){
    DataBase DB = createDataBase(NULL,"123",true);
    DB->put(DB,"1","123","1121323");
    DB->put(DB,"2","123","2121323");
    DB->put(DB,"3","123","3121323");
    DB->put(DB,"4","123","4121323");
    DB->put(DB,"5","123","5121323");
    DB->put(DB,"6","123","6121323");
    DB->put(DB,"7","123","7121323");
    DB->put(DB,"8","123","8121323");
    DB->put(DB,"9","123","9121323");
    //DB->put(DB,"9","asdasd","12132334");
    //DB->put(DB,"9","asdasd","1213444");
    DB->put(DB,"4","131","34243");
    DB->remove(DB,"9","123");
    printf("%d#%d\n",DB->size,DB->listSize);
    printf("%s\n",(char*)DB->get(DB,"9","123"));
    printf("%d#%d\n",DB->size,DB->listSize);
    //Table tab = createTable(true);
    /*tab->put(tab,"123","234");
    printf("%s\n",tab->get(tab,"123"));
    tab->remove(tab,"123");*/
    //DB->list[9].remove(&DB->list[9],"35");
    return 0;
}