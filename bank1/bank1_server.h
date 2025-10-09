/* bank1_server.h */

#pragma once

#include "../shared/bank1.h"
#include <string>
#include <iostream>
#include <sqlite3.h>
#include <cstring>
#include <sqlite3.h>

#define CREDIT 0
#define DEBIT 1
int* b1_change_balance(char* acctName, int amount, int operationMode);
