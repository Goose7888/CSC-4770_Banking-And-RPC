/* bank2_server.h */

#pragma once

#include "../shared/bank2.h"
#include <string>
#include <iostream>
#include <sqlite3.h>
#include <cstring>
#include <sqlite3.h>

#define CREDIT 0
#define DEBIT 1
#define SQLITE3_DB2 "bank2.db"
int* b2_change_balance(char* acctName, int amount, int operationMode);
