/* client.h */

#pragma once

#include <string>
#include <unordered_map>
#include <sys/types.h>
#include <iostream>
#include "../shared/vbank.h"

// Types:
typedef std::string Account;
typedef std::unordered_map<std::string, std::string> Arguments;


// Function Declarations:

// parses cmd line parameters to determine operation
Arguments* parseArgs(int argc, char** argv);
void printUsage(char** argv);
