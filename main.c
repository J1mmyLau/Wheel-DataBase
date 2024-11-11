// main.c

#include <stdio.h>
#include "DataBase.h"

int main() {
    // Create a new database
    DataBase DB = createDataBase(NULL, "MyDatabase", true);

    // Put entries into the database
    DB->put(DB, "Table1", "Key1", "Value1");
    DB->put(DB, "Table2", "Key2", "Value2");
    DB->put(DB, "Table2", "Key1", "Value3");
    DB->put(DB, "Table3", "Key1", "Value3");
    DB->put(DB, "Table4", "Key1", "Value3");
    DB->put(DB, "Table5", "Key1", "Value3");
    DB->put(DB, "Table6", "Key1", "Value3");
    DB->put(DB, "Table7", "Key1", "Value3");
    DB->put(DB, "Table8", "Key1", "Value3");
    DB->put(DB, "Table9", "Key1", "Value3");
    DB->put(DB, "Table10", "Key1", "Value3");
    DB->put(DB, "Table11", "Key1", "Value3");
    DB->put(DB, "Table12", "Key1", "Value3");
    printf("%d#%d\n",DB->size,DB->listSize);
    // Get entries from the database
    char *val1 = (char *)DB->get(DB, "Table1", "Key1");
    char *val2 = (char *)DB->get(DB, "Table2", "Key2");
    char *val3 = (char *)DB->get(DB, "Table2", "Key1");

    // Print the retrieved values
    printf("Table1, Key1: %s\n", val1);
    printf("Table1, Key2: %s\n", val2);
    printf("Table2, Key1: %s\n", val3);

    // Check if a key exists
    if (DB->exists(DB, "Table1", "Key1")) {
        printf("Key1 exists in Table1\n");
    }

    // Remove an entry
    DB->remove(DB, "Table1", "Key1");
    printf("%d#%d\n",DB->size,DB->listSize);

    // Check if the key still exists
    if (!DB->exists(DB, "Table1", "Key1")) {
        printf("Key1 has been removed from Table1\n");
    }

    // Clear the database
    DB->clear(DB);

    // Free the database
    free(DB);

    return 0;
}