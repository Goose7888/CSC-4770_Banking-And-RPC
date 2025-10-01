/* bank-server.cpp */

#include "bank_server.h"

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_db>" << std::endl;
        return 1;
    }

    sqlite3* db = initServer(argv[1]);

    return 0;
}

sqlite3* initServer(std::string dbPath) {
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
