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
    *iterator = NULL;
}
DBIterator nextDBIterator(DBIterator iterator){
    if(hasNextDBIterator(iterator)){
        if(iterator->tab != NULL && iterator->tab->next != NULL){
            iterator->count++;
            iterator->tab=iterator->tab->next;
            return iterator;
        }
        while(++iterator->hashCode < iterator->DB->listSize){
            Table tab = &iterator->DB->list[iterator->hashCode];
            if(tab->name != NULL){
                iterator->count++;
                iterator->tab = tab;
                break;
            }
        }
    }
    return iterator;
}
void resetDataBase(DataBase DB,int listSize){
    if(listSize < 8) return;
    Table tempList = newTableList(listSize);
    DBIterator iterator = createDBIterator(DB);
    int length = DB->size;
    for(int index = 0; hasNextDBIterator(iterator);index++){
        iterator = nextDBIterator(iterator);
        tempList[index].name = iterator->tab->name;
        tempList[index].map = iterator->tab->map;
        tempList[index].next = NULL;
    }
    freeDBIterator(&iterator);
    DB->size = 0;
    for(int i=0;i < DB->listSize;i++){
        Table current = &DB->list[i];
        current->name = NULL;
        current->map = NULL;
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
        //free(relist); //!!!
        relist = NULL;
    }
    for(int i=0; i < length; i++){
        DB->putT(DB,&tempList[i]);
    }
    //free(tempList);
    //tempList = NULL;
}
void defaultputT2DB(DataBase DB,Table tab){
    int index = DB->hashCode(DB,tab->name);
    if(DB->list[index].name == NULL){
        DB->list[index] = *createTable(DB->autoAssign);
        DB->size++;
        DB->list[index].map = tab->map;
        DB->list[index].name = tab->name;

    }
    else{
        Table current = &DB->list[index];
        while(current != NULL){
            if(DB->equal(tab->name,current->name)){
                current->map = tab->map;
                current->name = tab->name;
            }
            current = current->next;
        }
        Table temp = createTable(DB->autoAssign);
        temp->map = tab->map;
        temp->name = tab->name;
        temp->next = DB->list[index].next;
        DB->list[index].next = temp;//!!!
        DB->size++;
    }
}
void defaultPutDB(DataBase DB,void* nameT,void* key,void* value){
    if(DB->autoAssign && DB->size >= DB->listSize){
        resetDataBase(DB,DB->listSize * 2);
    }
    int index = DB->hashCode(DB,nameT);
    if(DB->list[index].name == NULL){
        DB->size++;
        DB->list[index].map=createTable(DB->autoAssign)->map;
        DB->list[index].name = nameT;
        DB->list[index].map->put(DB->list[index].map,key,value);//!!!
        printf("Create Table:%s, Hashcode:%d\n",(char*)nameT,index);
    }
    else{
        Table current = &DB->list[index];
        while(current != NULL){
            if(DB->equal(nameT,current->name)){
                current->map->put(current->map,key,value);
                return;
            }
            current = current->next;
        };
        Table tab = createTable(DB->autoAssign);
        tab->name = nameT;
        tab->map->put(tab->map,key,value);
        DB->list[index].next = tab;
        printf("Create Table:%s, Hashcode:%d\n",(char*)nameT,index);
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
        result=tab->map->remove(tab->map,key);
        if(tab->map->size == 0){
            if(tab->next != NULL){
                Table temp = tab->next;
                tab->name = temp->name;
                tab->map = temp->map;
                tab->next = temp->next;
                free(temp);
            }
            else{
                //printf("##%s\n",(char*)tab->name);
                tab->clear(tab);
            }
            DB->size--; 
        }
    }
    else{
        Table p = tab;
        tab = tab->next;
        while(tab != NULL){
            if(DB->equal(tab->name,nameT)){
                result=tab->map->remove(tab->map,key);
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
    if(result && DB->autoAssign && DB->size < DB->listSize / 2){
        resetDataBase(DB,DB->listSize / 2);
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
        return tab->map->exists(tab->map,key);
    }
    if(tab->next != NULL){
        do{
            if(DB->equal(tab->name,nameT)){
                return tab->map->exists(tab->map,key);
            }
            tab = tab->next;
        }while(tab->next != NULL);
        return false;
    }
    else{
        return false;
    }
}
void defaultClearDB(DataBase DB){
    for(int i=0;i<DB->listSize;i++){
        Table tab = DB->list[i].next;
        while(tab != NULL){
            Table next = tab->next;
            free(tab);
            tab = next;
        }
        DB->list[i].next = NULL;
    }
    free(DB->list);
    DB->list = NULL;
    DB->size = -1;
    DB->listSize = 0;
}
DataBase createDataBase(HashCodeDB hashCode,void* name,bool autoassign){
    DataBase DB = newDataBase();
    DB->size = 0;
    DB->listSize = 8;
    DB->hashCode = hashCode == NULL ? defaultHashCodeDB : hashCode;
    DB->name = name;
    DB->putT =defaultputT2DB;
    DB->equal = defaultEqual;
    DB->exists = defaultExistsDB;
    DB->get = defaultGetDB;
    DB->put = defaultPutDB;
    DB->remove = defaultRemoveDB;
    DB->clear = defaultClearDB;
    DB->autoAssign = autoassign;
    DB->list = newTableList(DB->listSize);
    Table p = DB->list;
    for(int i=0;i<DB->listSize;i++){
        //p[i] = *createTable(autoassign);
        p[i].name = NULL;
        p[i].next = NULL;
        p[i].map = createHashMap(NULL,NULL,autoassign);
        p[i].clear = defaultClearT;
        p[i].exists = defaultExistsT;
        p[i].get = defaultGetT;
        p[i].put = defaultPutT;
        p[i].remove = defaultRemoveT;
        p[i].fix_time = 0;
        //p[i].map->clear(p[i].map);
    }
    return DB;
}
int defaultHashCodeDB(DataBase DB,void* nameT){
    char *k=(char*)nameT;
    unsigned long h=0;
    while(*k){
        h = (h<<4) + *k++;
        unsigned long g = h & 0xf0000000L;
        if(g){
            h^= g>>24;
        }
        h &= ~g;
    }
    return h% DB->listSize;
}