/* bank_server.h */

#pragma once

#include <iostream>
#include <string>
#include <sqlite3.h>

typedef std::string Account;

sqlite3* initServer(std::string dbPath);
void credit(Account acct, int amount);
void debit(Account acct, int amount);
// transfers will be done by the virtual bank
