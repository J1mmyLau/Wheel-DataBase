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
    HashMap map;
    PutT put;
    GetT get;
    RemoveT remove;
    ClearT clear;
    ExistsT exists;
    bool autoAssign;
}* Table;
Table createTable(char* name,bool autoassign);
void defaultPutT(Table tab,void *key,void *value);
void* defaultGetT(Table tab,void *key);
bool defaultRemoveT(Table tab, void *key);
bool defaultExistsT(Table tab, void *key);
void defaultClearT(Table tab);
#define newTable() (Table)malloc(sizeof(Table));
typedef struct dataBase
{
    int size;
    int listSize;
    HashCode hashCode;

}* DataBase;
#endif