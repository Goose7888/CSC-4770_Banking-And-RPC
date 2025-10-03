/* bank-server.cpp */

#include "bank_server.h"
#include <sqlite3.h>

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
        sqlite3_close(db);
        return 1;
    }

    initDB(db);

    sqlite3_close(db);
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

void initDB(sqlite3* db) {

    std::string zStmt = "SELECT * FROM sqlite_master WHERE type=\'table\' AND name=\'Accounts\';";

    sqlite3_stmt* ppStmt = nullptr;
    const char* pzTail = nullptr;
    if (sqlite3_prepare_v2(db, zStmt.c_str(), zStmt.length(), &ppStmt, &pzTail) != SQLITE_OK) {
        std::cerr << "Cannot prepare statement!" << std::endl;
        return;
    }

    // If no results, Accounts table needs to be created
    if (sqlite3_step(ppStmt) == SQLITE_DONE) {
        zStmt = "CREATE TABLE Accounts (ID TEXT PRIMARY KEY, Balance INT NOT NULL)";
        sqlite3_stmt* ctblStmt = nullptr;
        if (sqlite3_prepare_v2(db, zStmt.c_str(), zStmt.length(), &ctblStmt, &pzTail) != SQLITE_OK) {
            std::cerr << "Cannot prepare statement!" << std::endl;
            return;
        }

        std::cout << sqlite3_step(ctblStmt) << std::endl;
    }

    // At this point, the Accounts table now exists 🎉🎉
    sqlite3_finalize(ppStmt);
}

void credit(Account acct, int amount) {

}

void debit(Account acct, int amount) {

}
