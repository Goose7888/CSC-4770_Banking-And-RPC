/* bank_init.h */

#pragma once

#include <iostream>
#include <string>
#include <sqlite3.h>

typedef std::string Account;

// Defines who the program will do banking for
enum operation_mode {
    BANK1,
    BANK2
};

sqlite3* initServer(int operation_mode);
void initDB(sqlite3* db);
// transfers will be done by the virtual bank
