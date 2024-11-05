#ifndef DATABASE_H
#define DATABASE_H
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<stdbool.h>
#include "HashMap.h"
typedef struct table *Table;
typedef void(*PutT)(Table tab,void *key,void *value);
typedef void*(*GetT)(Table tab,void *key);
typedef bool(*RemoveT)(Table tab,void *key);
typedef void(*ClearT)(Table tab);
typedef bool(*ExistsT)(Table tab,void *key);
typedef struct table{
    char* name;
    long fix_time;
    struct table *next;
    HashMap map;
    PutT put;
    GetT get;
    RemoveT remove;
    ClearT clear;
    ExistsT exists;
    bool autoAssign;
}* Table;
Table createTable(bool autoassign);
void defaultPutT(Table tab,void *key,void *value);
void* defaultGetT(Table tab,void *key);
bool defaultRemoveT(Table tab, void *key);
bool defaultExistsT(Table tab, void *key);
void defaultClearT(Table tab);
#define newTable() (Table)malloc(sizeof(struct table))
#define newTableList(length) (Tabel)malloc(length*sizeof(struct table))
typedef struct dataBase* DataBase;
DataBase createDataBase(void* name,bool autoassig);
//typedef bool(*EqualDB)(void* name1,void* name2);
typedef void(*PutDB)(DataBase DB,void* nameT,void* key,void* value);
typedef void*(*GetDB)(DataBase DB,void* nameT,void* key);
typedef bool(*ExistsDB)(DataBase DB,void* nameT,void* key);
typedef bool(*RemoveDB)(DataBase DB,void* nameT,void* key);
typedef void(*ClearDB)(DataBase DB);
typedef struct dataBase{
    int size;
    int listSize;
    void* name;
    HashCode hashCode;
    Table list;
    Equal equal;
    PutDB put;
    GetDB get;
    RemoveDB remove;
    ExistsDB exists;
    ClearDB clear;
    bool autoAssign;
}* DataBase;
#define newDataBase() (DataBase)malloc(sizeof(struct dataBase));
int defaultHashCodeDB(DataBase DB,void nameT);
void defaultPutDB(DataBase DB,void* nameT,void* key,void* value);
void* defaultGetDB(DataBase DB,void* nameT,void* key);
bool defaultRemoveDB(DataBase DB,void* nameT,void* key);
bool defaultExistsDB(DataBase DB,void* nameT,void* key);
void defaultClearDB(DataBase);
void resetDataBase(DataBase DB,int listSize);
typedef struct dbIterator{
    Table tab;
    int count;
    int hashCode;
    DataBase DB;
}* DBIterator;
#define newDBIterator() (DBIterator)malloc(sizeof(struct dbIterator))
DBIterator createDBIterator(DataBase DB);
bool hasNextDBIterator(DBIterator iterator);
DBIterator nextDBIterator(DBIterator iterator);
void freeDBIterator(DBIterator *iterator);
#endif