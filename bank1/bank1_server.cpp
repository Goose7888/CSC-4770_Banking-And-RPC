/* bank1_server.cpp */

#include "bank1_server.h"


int* b1_credit_1_svc(char* acctName, int amount, struct svc_req*) {
    int* result = nullptr;
    // account* acct = b1_acct_lookup_1_svc(*acctName, nullptr);
    account* acct = nullptr;

    if (acct == NULL) {
        std::cerr << "Error! Could not connect to remote precedure!" << std::endl;
        *result = 1;
        return result;
    }

    if (acct->errorcode != 0)
    {
        std::cerr << "Account does not exist!" << std::endl;
        *result = 1;
        return result;
    }

    *result = 0;
    return result;
}

int* b1_debit_1_svc(char* acctName, int amount, struct svc_req*) {
    int* result = nullptr;
    // account* acct = b1_acct_lookup_1_svc(*acctName, nullptr);
    account* acct = nullptr;

    if (acct == NULL) {
        std::cerr << "Error! Could not connect to remote precedure!" << std::endl;
        *result = 1;
        return result;
    }

    if (acct->errorcode != 0)
    {
        std::cerr << "Account does not exist!" << std::endl;
        *result = 1;
        return result;
    }

    *result = 0;
    return result;
}

account* b1_acct_lookup_1_svc(char* acct, struct svc_req *) {

    std::string zStmt = "SELECT FROM accounts ";

    sqlite3* ppDb;
    sqlite3_stmt* ppStmt;

    sqlite3_open("bank1.db", &ppDb);

    //sqlite3_prepare_v2(sqlite3 *db, const char *zSql, int nByte, sqlite3_stmt **ppStmt, const char **pzTail);

    sqlite3_close(ppDb);

}
