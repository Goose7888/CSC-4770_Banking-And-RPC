/* bank1_server.cpp */

#include "bank1_server.h"

int* b1_credit_1_svc(char* acctName, int amount, struct svc_req*) {
    return b1_change_balance(acctName, amount, CREDIT);
}

int* b1_debit_1_svc(char* acctName, int amount, struct svc_req*) {
    return b1_change_balance(acctName, amount, DEBIT);
}

int* b1_change_balance(char* acctName, int amount, int operationMode) {
    static int ret = 0;

    account* acct = b1_acct_lookup_1_svc(acctName, nullptr);

    if (acct == NULL) {
        std::cerr << "Error! Could not connect to remote precedure!" << std::endl;
        ret = 1;
        return &ret;
    }

    if (acct->errorcode != 0)
    {
        std::cerr << "Account does not exist!" << std::endl;
        ret = 1;
        return &ret;
    }

    char buildStmt[256] = "";
    int newBalance = 0;

    if (operationMode == CREDIT) {
        newBalance = acct->balance + amount;
    }
    else if (operationMode == DEBIT) {
        newBalance = acct->balance - amount;
        if (newBalance < 0) {
            std::cerr << "Bank does not support negative balances!" << std::endl;
            ret = 1;
            return &ret;
        }
    }

    sqlite3* ppDb;
    sqlite3_stmt* ppStmt;
    const char* pzTail;
    const char* zSql = buildStmt;
    int sqlite3Res;

    sqlite3Res = sqlite3_open("bank1.db", &ppDb);
    if (sqlite3Res != SQLITE_OK) {
        std::cout << "Error opening \"bank1.db\"!" << std::endl;
        ret = 1;
        return &ret;
    }

    sprintf(buildStmt, "UPDATE Accounts SET Balance=%d WHERE ID = \'%s\';", newBalance, acct->id);

    sqlite3Res = sqlite3_prepare_v2(ppDb, zSql, strlen(zSql), &ppStmt, &pzTail);

    if (sqlite3Res != SQLITE_OK) {
        std::cerr << "Error preparing statement!" << std::endl;
        ret = 1;
        return &ret;
    }

    sqlite3Res = sqlite3_step(ppStmt);
    if (sqlite3Res != SQLITE_DONE) {
        std::cerr << "SQL Execution not successful!" << std::endl;
        ret = 1;
        return &ret;
    }

    sqlite3_finalize(ppStmt);

    ret = 0;
    return &ret;
}

account* b1_acct_lookup_1_svc(char* acct, struct svc_req *) {
    static account ret;
    static char acct_id[128] = "";

    ret.id = acct_id;

    char buildStmt[256] = "";
    const char* zSql = buildStmt;
    sqlite3* ppDb;
    sqlite3_stmt* ppStmt;
    const char* pzTail;
    int sqlite3Res = 0;

    sprintf(buildStmt, "SELECT balance FROM Accounts WHERE ID = \'%s\';", acct);

    if (sqlite3_open("bank1.db", &ppDb) != SQLITE_OK) {
        std::cerr << "Cannot open \"bank1.db\"!" << std::endl;
        std::cerr << sqlite3_open("bank1.db", &ppDb) << std::endl;
    }

    sqlite3Res = sqlite3_prepare_v2(ppDb, zSql, strlen(zSql),  &ppStmt, &pzTail);

    if (sqlite3Res != SQLITE_OK) {
        std::cerr << "Cannot prepare statement!" << std::endl;
        std::cerr << "Error: " << sqlite3Res << std::endl;
        ret.errorcode = 1;
        ret.balance = 0;
        return &ret;
    }

    sqlite3Res = sqlite3_step(ppStmt);
    while (sqlite3Res != SQLITE_DONE) {
        ret.balance = sqlite3_column_int(ppStmt, 0);
        sqlite3Res = sqlite3_step(ppStmt);
    }

    sqlite3_finalize(ppStmt);
    sqlite3_close(ppDb);

    ret.errorcode = 0;
    strcpy(acct_id, acct);

    return &ret;
}
