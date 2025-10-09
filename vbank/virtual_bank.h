/* virtual_bank.h */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "../shared/vbank.h"
#include "../shared/bank1.h"

#define BANK1_ADDR "localhost"
#define BANK2_ADDR "localhost"

#define CREDIT 0
#define DEBIT 1

int* vb_change_balance(char* acct, int amount, int operation_mode);
