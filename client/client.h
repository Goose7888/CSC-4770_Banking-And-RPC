/* client.h */

#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>

//// Types:
typedef std::string Account;
typedef std::unordered_map<std::string, std::string> Arguments;

//// Function Definitions:

// credits an account
void credit(Account acct);

// debits an account
void debit(Account acct);

// transfers money by creditting acct_a and debitting acct_b
void transfer(Account acct_a, Account acct_b);

// parses cmd line parameters to determine operation
Arguments parseArgs(int argc, char** argv);
