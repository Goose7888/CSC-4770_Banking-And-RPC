/* bank1_server.cpp */

#include "bank1_server.h"
#include <cstring>
#include <sqlite3.h>


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
    static char acct_id[128] = "";

    ret.id = acct_id;

    char buildStmt[256] = "";
    const char* zStmt = buildStmt;
    sqlite3* ppDb;
    sqlite3_stmt* ppStmt;
    const char* pzTail;
    int sqlite3Res = 0;


    sprintf(buildStmt, "SELECT balance FROM Accounts WHERE id = \'%s\';", acct);
    std::cout << "zStmt: " << zStmt << std::endl << "Length: " << strlen(zStmt) << std::endl;

    std::string testStmt = "SELECT * FROM Accounts;";

    if (sqlite3_open("bank1.db", &ppDb) != SQLITE_OK) {
        std::cerr << "Cannot open \"bank1.db\"!" << std::endl;
        std::cerr << sqlite3_open("bank1.db", &ppDb) << std::endl;
    }

    sqlite3Res = sqlite3_prepare_v2(ppDb, zStmt, strlen(zStmt),  &ppStmt, &pzTail);

    std::cout << sqlite3Res << std::endl;

    if (sqlite3Res != SQLITE_OK) {
        std::cerr << "Cannot prepare statement!" << std::endl;
        std::cerr << "Error: " << sqlite3Res << std::endl;
        ret.errorcode = 1;
        ret.balance = 0;
        return &ret;
    }

    sqlite3Res = sqlite3_step(ppStmt);
    while (sqlite3Res != SQLITE_DONE) {
        std::cout << "Result: " << sqlite3Res << std::endl;
        ret.balance = sqlite3_column_int(ppStmt, 0);
        std::cout << ret.balance << std::endl;

        sqlite3Res = sqlite3_step(ppStmt);
    }


    sqlite3_finalize(ppStmt);
    sqlite3_close(ppDb);

    ret.errorcode = 0;
    strcpy(acct_id, acct);

    return &ret;
}
