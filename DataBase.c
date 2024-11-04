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
Table createTable(bool autoassign){
    Table tab = newTable();
    tab->name = NULL;
    tab->map = createHashMap(NULL,NULL,autoassign);
    tab->fix_time = time(NULL);
    tab->clear = defaultClearT;
    tab->exists = defaultExistsT;
    tab->get = defaultGetT;
    tab->put = defaultPutT;
    tab->remove = defaultRemoveT;
    tab->next = NULL;
    return tab;
}
DBIterator createDBIterator(DataBase DB){
    DBIterator iterator = newDBIterator();
    iterator->DB = DB;
    iterator->count = 0;
    iterator->hashCode = -1;
    iterator->tab = NULL;
    return iterator;
}
bool hasNextDBIterator(DBIterator iterator){
    return iterator->count < iterator->DB->size ? true:false;
}
void freeDBIterator(DBIterator* iterator){
    free(*iterator);
    *iterator = NULL
}
DBIterator nextDBIterator(DBIterator iterator){
    if(hasNextDBIterator(iterator)){
        if(iterator->tab != NULL && iterator->tab->next != NULL){
            iterator->count++;
            iterator->tab=iterator->tab->nextl
            return iterator;
        }
        while(++iterator->hashCode < iterator->DB->listSize){
            Table tab = &iterator->DB->list[iterator->hashCode];
            if(tab->name != NULL){
                iterator->count++;
                iterator.tab = tab;
                break;
            }
        }
    }
    return iterator;
}
void freeDBIterator(DBIterator* iterator){
    free(*iterator);
    *iterator = NULL;
}
void resetDataBase(DataBase DB,int listSize){
    if(listSize < 8) return;
    Table tempList = newTableList(listSize);
    DBIterator iterator = createDBIterator(DB);
    int length = DB->size;
    for(int index =0; hasNextDBIterator(iterator);index++){
        iterator = nextHashMapIterator(iterator);
        tempList[index].name = iterator->tab->name;
        tempList[index].map = iterator->tab->map;
        tempList[index].next = NULL;
    }
    freeDBIterator(&iterator);
    DB->size = 0;
    for(int i=0; DB->listSize;i++){
        Table current = &DB->list[i];
        current->name = NULL;
        current->map =NULL;
        if(current->next != NULL){
            while(current->next !=NULL){
                Table temp = current->next->next;
                free(current->next);
                current->next = temp;
            }
        }
    }
    DB->listSize = listSize;
    Table relist = (Table)realloc(DB->list,DB->listSize * sizeof(struct table));
    if(relist != NULL){
        DB->list = relist;
        free(relist); //!!!
        relist = NULL;
    }
    for(int i=0; i < length; i++){
        DB->put(DB,tempList[i].name,tempList[i].map);
    }
    free(tempList);
    tempList = NULL;
}
void defaultPutDB(DataBase DB,void* nameT,void* key,void* value){
    if(DB->autoAssign && DB->size >= DB->listSize){
        resetDataBase(DB,DB->listSize * 2);
    }
    int index = DB->hashCode(DB,nameT);
    if(DB->list[index].name == NULL){

        DB->size++;
        DB->list[index]=createTable(true);
        DB->list[index].name = nameT;
        DB->list->map->put(DB->list->map,key,value);
        printf("Create Table:%s, Hashcode:%d",nameT,index);
    }
    else{
        Table current = &DB->list[index];
        while(current !NULL){
            if(DB->equal(nameT,current->name)){
                current->map->put(current->map,key,value);
            }
            current = current->next;
        };
        Table tab = newTable();
        tab->name = nameT;
        tab->map->put(tab->map,key,value);
        DB->list[index].next = entry;
        DB->size++;
    }
}
void* defaultGetDB(DataBase DB,void* nameT,void* key){
    int index = DB->hashCode(DB,nameT);
    Table tab = &DB->list[index];
    while(tab->name != NULL && !DB->equal(tab->name,nameT)){
        tab = tab->next;
    }
    return tab->map->get(tab->map,key);
}
bool defaultRemoveDB(DataBase DB,void* nameT,void* key){
    int index = DB->hashCode(DB,nameT);
    Table tab = &DB->list[index];
    if(tab->name == NULL){
        return false;
    }
    bool result = false;
    if(DB->equal(tab->name,nameT)){
        result=tab->remove(tab,key);
        if(tab->map->size == 0){
            if(tab->next != NULL){
                Table temp = tab->next;
                tab->name = temp->name;
                tab->map = temp->map;
                tab->next = temp->next;
                free(temp);
            }
            else{
                tab->clear;
            }
            DB->size--; 
        }
    }
    else{
        Table p = tab;
        tab = tab->next;
        while(tab != NULL){
            if(DB->equal(tab->name,nameT)){
                result=tab->remove(tab,key);
                if(tab->map->size == 0){
                    p->next = tab->next;
                    free(tab);
                    DB->size--;
                    break;
                }
            }
            p = tab;
            tab = tab->next;
        }
    }
    return result;
}
bool defaultExistsDB(DataBase DB,void* nameT,void* key){
    int index = DB->hashCode(DB,nameT);
    Table tab = &DB->list[index];
    if(tab->name == NULL) {
        return false;
    }
    if(DB->equal(tab->name,nameT)){
        do{
            
        }
    }
}
