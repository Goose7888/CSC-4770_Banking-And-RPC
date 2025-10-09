/* bank2_server.cpp */

#include "bank2_server.h"

int* b2_credit_1_svc(char* acctName, int amount, struct svc_req*) {
    return b2_change_balance(acctName, amount, CREDIT);
}

int* b2_debit_1_svc(char* acctName, int amount, struct svc_req*) {
    return b2_change_balance(acctName, amount, DEBIT);
}

int* b2_change_balance(char* acctName, int amount, int operationMode) {
    static int ret = 0;

    b2_account* acct = b2_acct_lookup_1_svc(acctName, nullptr);

    if (acct == NULL) {
        std::cerr << "Error! Could not connect to remote precedure!" << std::endl;
        ret = 1;
        return &ret;
    }

    if (acct->errorcode != 0)
    {
        std::cerr << "Account does not exist!" << std::endl;
        ret = 2;
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

    sqlite3Res = sqlite3_open(SQLITE3_DB2, &ppDb);
    if (sqlite3Res != SQLITE_OK) {
        std::cout << "Error opening \"bank2.db\"!" << std::endl;
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

b2_account* b2_acct_lookup_1_svc(char* acct, struct svc_req *) {
    static b2_account ret;
    static char acct_id[128] = "ERROR!!";

    ret.id = acct_id;

    char buildStmt[256] = "";
    const char* zSql = buildStmt;
    sqlite3* ppDb;
    sqlite3_stmt* ppStmt;
    const char* pzTail;
    int sqlite3Res = 0;

    sprintf(buildStmt, "SELECT balance FROM Accounts WHERE ID = \'%s\';", acct);

    if (sqlite3_open(SQLITE3_DB2, &ppDb) != SQLITE_OK) {
        std::cerr << "Cannot open \"bank2.db\"!" << std::endl;
        std::cerr << sqlite3_open(SQLITE3_DB2, &ppDb) << std::endl;
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

    // This block occurs when no account has been returned
    if (sqlite3Res == SQLITE_DONE) {
        ret.errorcode = 1;
        ret.balance = 0;
        return &ret;
    }

    ret.balance = sqlite3_column_int(ppStmt, 0);
    ret.errorcode = 0;
    strcpy(acct_id, acct);

    sqlite3_finalize(ppStmt);
    sqlite3_close(ppDb);

    return &ret;
}
