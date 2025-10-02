/* bank-server.cpp */

#include "bank_server.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " [--bank1] [--bank2]" << std::endl;
        return 1;
    }

    std::string argument = argv[1];
    int operation_mode;
    if (argument == "--bank1") {
        operation_mode = BANK1;
    }
    else if (argument == "--bank2") {
        operation_mode = BANK2;
    }
    else {
        std::cerr << "Usage: " << argv[0] << " [--bank1] [--bank2]" << std::endl;
        return 1;
    }

    sqlite3* db = initServer(operation_mode);
    if (db == nullptr) {
        return 1;
    }

    return 0;
}

sqlite3* initServer(int operation_mode) {
    std::string dbPath = "";
    if (operation_mode == BANK1) {
        dbPath = "bank1.db";
    }
    else if (operation_mode == BANK2) {
        dbPath = "bank2.db";
    }
    else {
        std::cerr << "Invalid operation mode!";
        return nullptr;
    }

    sqlite3* db;
    if (sqlite3_open(dbPath.c_str(), &db) != SQLITE_OK) {
        std::cerr << "Cannot open " << dbPath << std::endl;
        return nullptr;
    }
    return db;
}

void credit(Account acct, int amount) {

}

void debit(Account acct, int amount) {

}
