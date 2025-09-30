/* client.h */

#pragma once

//// Includes:
#include <string>
#include <unordered_map>

//// Types:
typedef std::string Account;

//// Function Definitions:

// credits an account
void credit(Account acct);

// debits an account
void debit(Account acct);

// transfers money between accounts by crediting one account
// and debitting the other
void transfer(Account acct_a, Account acct_b);

// parses cmd line parameters to determine operation
std::unordered_map<std::string, std::string> parse_args(int argc, char* argv[]);
