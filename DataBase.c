#include "HashMap.h"
#include "DataBase.h"
void defaultClearT(Table tab){
    tab->map->clear(tab->map);
    tab->fix_time = time(NULL);
    tab->name = NULL;
}
bool defaultExistsT(Table tab,void* key){
    return tab->map->exists(tab->map,key);
}
void* defaultGetT(Table tab,void* key){
    return tab->map->get(tab->map,key);
}
void defaultPutT(Table tab,void* key,void *value){
    tab->fix_time = time(NULL);
    return tab->map->put(tab->map,key,value);
}
bool defaultRemoveT(Table tab,void* key){
    if(tab->map->remove(tab->map,key)){
    tab->fix_time = time(NULL);
    return true;
    }
    return false;
}
Table createTable(char* name,bool autoassign){
    Table tab = newTable();
    tab->name = name;
    tab->map = createHashMap(NULL,NULL,autoassign);
    tab->fix_time = time(NULL);
    tab->clear = defaultClearT;
    tab->exists = defaultExistsT;
    tab->get = defaultGetT;
    tab->put = defaultPutT;
    tab->remove = defaultRemoveT;
    return tab;
}