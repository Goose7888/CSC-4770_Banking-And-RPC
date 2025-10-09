/* virtual_bank.h */

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include "../shared/vbank.h"
#include "../shared/bank1.h"
#include "../shared/bank2.h"

#define BANK1_ADDR "localhost"
#define BANK2_ADDR "localhost"

#define NO_BANK  0
#define BANK1  1
#define BANK2  2

#define CREDIT 0
#define DEBIT 1

int* vb_change_balance(char* acct, int amount, int operation_mode);
bool change_balance(char* acct_name, int amount, int operation_mode, int bank_location);
bool get_acct(char* acct_name, int bank_location);
int get_acct_location(char* acct_name);
