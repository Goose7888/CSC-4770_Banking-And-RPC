/* client.cpp */

#include "client.h"

int main(int argc, char** argv) {
    Arguments args = parseArgs(argc, argv);

    int amount = stoi(args["amount"]);
    if (amount < 0) {
        throw std::out_of_range("Negative amounts not allowed!");
    }

    if (args["operationMode"] == "credit") {
        credit(args["acct_a"], stoi(args["amount"]));
    }
    else if (args["operationMode"] == "debit") {
        debit(args["acct_a"], stoi(args["amount"]));
    }
    else if (args["operationMode"] == "transfer") {
        transfer(args["acct_a"], args["acct_b"], stoi(args["amount"]));
    }
    else {
        throw std::invalid_argument("Invalid operation mode!");
    }

    return 0;
}

void credit(Account acct, int amount) {
    // Use RPC to write to `int VB_credit(string account, int amount)`
}

void debit(Account acct, int amount) {
    // Use RPC to write to `int VB_debit(string account, int amount)`
}

void transfer(Account acct_a, Account acct_b, int amount) {
    // Use RPC to write to `int VB_transfer(string account1, string account2, int amount)`
}

Arguments parseArgs(int argc, char** argv) {
    Arguments args;

    if (argc < 4) {
        throw std::invalid_argument("Not enough arguments!");
    }

    args["operationMode"] = argv[1];
    args["acct_a"] = argv[2];

    if (args["operationMode"] == "transfer") {
        if (argc < 4) {
            throw std::invalid_argument("Not enough arguments!");
        }
        args["acct_b"] = argv[3];
    }
    else {
        args["amount"] = argv[3];
    }

    return args;
}
