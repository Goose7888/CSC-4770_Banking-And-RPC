/* client.h */

#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>
#include <sys/types.h>

//// Types:
typedef std::string Account;
typedef std::unordered_map<std::string, std::string> Arguments;

//// Function Declarations:

// credits an account
void credit(Account acct, u_int amount);

// debits an account
void debit(Account acct, u_int amount);

// transfers money by creditting acct_a and debitting acct_b
void transfer(Account acct_a, Account acct_b, u_int amount);

// parses cmd line parameters to determine operation
Arguments parseArgs(int argc, char** argv);
