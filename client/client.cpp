/* client.cpp */

#include "client.h"

int main(int argc, char** argv) {
    Arguments args = parseArgs(argc, argv);

    return 0;
}

void credit(Account acct) {

}

void debit(Account acct) {

}

void transfer(Account acct_a, Account acct_b) {

}

Arguments parseArgs(int argc, char** argv) {
    Arguments args;

    if (argc < 3) {
        throw std::invalid_argument("Not enough arguments!");
    }

    args["operationMode"] = argv[1];
    args["acct_a"] = argv[2];

    if (args["operationMode"] == "transfer")
    {
        if (argc < 4) {
            throw std::invalid_argument("Not enough arguments!");
        }
        args["acct_b"] = argv[3];
    }

    return args;
}
