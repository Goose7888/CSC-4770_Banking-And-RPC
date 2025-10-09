/* bank1_server.cpp */

#include "bank1_server.h"
#include <cstring>


int* b1_credit_1_svc(char* acctName, int amount, struct svc_req*) {
    int* result = nullptr;
    account* acct = b1_acct_lookup_1_svc(acctName, nullptr);
    // account* acct = nullptr;

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

    char zStmt[256] = "";
    int newBalance = acct->balance + amount;

    sqlite3* ppDb;
    sqlite3_stmt* ppStmt;
    const char* pzTail;
    sqlite3_open("bank_1.db", &ppDb);

    sprintf(zStmt, "UPDATE accounts SET Balance %d WHERE ID = %s;", newBalance, acct->id);
    sqlite3_prepare_v2(ppDb, zStmt, 256, &ppStmt, &pzTail);

    std::cout << sqlite3_step(ppStmt) << std::endl;

    sqlite3_finalize(ppStmt);

    *result = 0;
    return result;
    *result = 0;
    return result;
}

int* b1_debit_1_svc(char* acctName, int amount, struct svc_req*) {
    static int result;

    account* acct = b1_acct_lookup_1_svc(acctName, nullptr);

    if (acct == NULL) {
        std::cerr << "Error! Could not connect to remote precedure!" << std::endl;
        result = 1;
        return &result;
    }

    if (acct->errorcode != 0)
    {
        std::cerr << "Account does not exist!" << std::endl;
        result = 1;
        return &result;
    }

    char zStmt[256] = "";
    int newBalance = acct->balance - amount;

    // Negative balances not supported
    if (newBalance < 0) {
        result = 2;
        return &result;
    }


    sqlite3* ppDb;
    sqlite3_stmt* ppStmt;
    const char* pzTail;
    sqlite3_open("bank_1.db", &ppDb);

    sprintf(zStmt, "UPDATE accounts SET Balance %d WHERE ID = %s;", newBalance, acct->id);
    sqlite3_prepare_v2(ppDb, zStmt, 256, &ppStmt, &pzTail);

    std::cout << sqlite3_step(ppStmt) << std::endl;
    std::cout << sqlite3_step(ppStmt) << std::endl;
    std::cout << sqlite3_step(ppStmt) << std::endl;

    sqlite3_finalize(ppStmt);

    result = 0;
    return &result;
}

account* b1_acct_lookup_1_svc(char* acct, struct svc_req *) {

    static account ret;

    char zStmt[256] = "";

    sprintf(zStmt, "SELECT balance FROM accounts WHERE id = %s;", acct);

    sqlite3* ppDb;
    sqlite3_stmt* ppStmt;
    const char* pzTail;

    sqlite3_open("bank1.db", &ppDb);

    sqlite3_prepare_v2(ppDb, zStmt, 256,  &ppStmt, &pzTail);

    std::cout << sqlite3_step(ppStmt) << std::endl;
    std::cout << sqlite3_step(ppStmt) << std::endl;
    std::cout << sqlite3_step(ppStmt) << std::endl;

    sqlite3_close(ppDb);

    ret.errorcode = 0;
    ret.balance = 0;
    strncpy(ret.id, "", 2);

    return &ret;
}
