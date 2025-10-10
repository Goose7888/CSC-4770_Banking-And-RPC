/* client.cpp */

#include "client.h"

int main(int argc, char** argv) {
    Arguments* args = parseArgs(argc, argv);
    if (args == nullptr) {
        printUsage(argv);
        return 1;
    }

    int amount = 0;
    if ((*args)["operationMode"] != "query") {
        amount = stoi((*args)["amount"]);
        if (amount < 0) {
            std::cerr << "Negative values not allowed!" << std::endl;
            printUsage(argv);
            return 1;
        }
    }

    CLIENT* clnt = nullptr;
    int* result = nullptr;
    std::string message = "";
    char* rawMessage;
    std::string server_addr = (*args)["serverAddress"];

    clnt = clnt_create(server_addr.c_str(), VBANKPROG, VBANKVERS, "tcp");

    if (clnt == NULL) {
        clnt_pcreateerror(server_addr.c_str());
        return 1;
    }

    if ((*args)["operationMode"] == "credit") {
        message = (*args)["acct_a"];
        rawMessage = new char[message.length() + 1];
        strcpy(rawMessage, message.c_str());

        result = vb_credit_1(rawMessage, stoi((*args)["amount"]), clnt);

        if (result == NULL) {
            std::cerr << "An error occured connecting to the virtual bank." << std::endl;
            delete [] rawMessage;
            clnt_destroy(clnt);
            return 1;
        }
        delete [] rawMessage;
    }
    else if ((*args)["operationMode"] == "debit") {
        message = (*args)["acct_a"];
        rawMessage = new char[message.length() + 1];
        strcpy(rawMessage, message.c_str());

        result = vb_debit_1(rawMessage, stoi((*args)["amount"]), clnt);

        if (result == NULL) {
            std::cerr << "An error occured connecting to the virtual bank." << std::endl;
            delete [] rawMessage;
            clnt_destroy(clnt);
            return 1;
        }
        delete [] rawMessage;
    }
    else if ((*args)["operationMode"] == "transfer") {

        // This is a little hacky

        std::string message1 = (*args)["acct_a"];
        std::string message2 = (*args)["acct_b"];

        char* rawMessage1 = new char[message1.length() + 1];
        strcpy(rawMessage1, message1.c_str());

        char* rawMessage2 = new char[message2.length() + 1];
        strcpy(rawMessage2, message2.c_str());

        result = vb_transfer_1(rawMessage1, rawMessage2, stoi((*args)["amount"]), clnt);
        if (result == NULL) {
            std::cerr << "An error occured connecting to the virtual bank." << std::endl;
            clnt_destroy(clnt);
            delete [] rawMessage1;
            delete [] rawMessage2;
            return 1;
        }

        delete [] rawMessage1;
        delete [] rawMessage2;
    }
    else if ((*args)["operationMode"] == "query") {
        std::string acct = (*args)["acct_a"];
        char* acct_cstr = new char[acct.length() + 1];
        strcpy(acct_cstr, acct.c_str());

        result = vb_query_1(acct_cstr, clnt);
        if (result == NULL) {
            std::cerr << "An error occured connecting to the virtual bank." << std::endl;
            clnt_destroy(clnt);
            delete [] acct_cstr;
            return 1;
        }
        if (*result == -1) {
            std::cerr << "Unable to look up account!" << std::endl;
            clnt_destroy(clnt);
            delete [] acct_cstr;
            return 1;
        }

        std::cout << "Account: " << acct << " Balance: " << *result << std::endl;
        *result = 0;
        delete [] acct_cstr;
    }
    else {
        std::cerr << "Invalid operation mode!" << std::endl;
        printUsage(argv);
        clnt_destroy(clnt);
        return 1;
    }

    if (*result == 0) {
        std::cout << "The operation completed successfully" << std::endl;
    }
    else {
        std::cout << "A problem occured in the virtual bank." << std::endl;
        std::cout << "Error code: " << *result << std::endl;
    }
    clnt_destroy(clnt);


    return 0;
}

Arguments* parseArgs(int argc, char** argv) {
    static Arguments args;

    if (argc < 4) {
        std::cerr << "Not enough arguments!" << std::endl;
        return nullptr;
    }

    args["serverAddress"] = argv[1];
    args["operationMode"] = argv[2];
    args["acct_a"] = argv[3];

    if (args["operationMode"] == "query" && argc < 4) {
        std::cerr << "Not enough arguments!" << std::endl;
        return nullptr;
    }
    else if (args["operationMode"] != "query" && argc < 5) {
        std::cerr << "Not enough arguments!" << std::endl;
        return nullptr;
    }

    if (args["operationMode"] == "transfer") {
        if (argc < 6) {
            std::cerr << "Not enough arguments!" << std::endl;
        }
        args["acct_b"] = argv[4];
        args["amount"] = argv[5];
    }
    else if (args["operationMode"] != "query") {
        args["amount"] = argv[4];
    }

    return &args;
}

void printUsage(char** argv) {
    std::cout << "Usage: " << argv[0] << " [SERVER_ADDRESS] [OPERATION] [ACCOUNT] ([ACCOUNT]) [AMOUNT]" << std::endl
        << "\tWhere [OPERATION] is one of:" << std::endl
        << "\t\t\"credit\": credit [AMOUNT] to [ACCOUNT]" << std::endl
        << "\t\t\"debit\": debit [AMOUNT] from [ACCOUNT]" << std::endl
        << "\t\t\"transfer\": transfer [AMOUNT] from first [ACCOUNT] to second [ACCOUNT]" << std::endl
        << "\t\t\"query\": print balance of [ACCOUNT]" << std::endl;
}
