/* bank_init.h */

#pragma once

#include <iostream>
#include <string>
#include <cstring>
#include <sqlite3.h>

typedef std::string Account;

// Defines who the program will do banking for
enum operation_mode {
    BANK1,
    BANK2
};

sqlite3* initServer(int operation_mode);
void initDB(sqlite3* db);
void fillAccounts(sqlite3* db, int operationMode);
void insertRecord(sqlite3* db, std::string acct_name, unsigned int balance);
