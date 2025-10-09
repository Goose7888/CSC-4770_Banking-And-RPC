/* virtual_bank.cpp */

#include "virtual_bank.h"
#include "rpc/clnt.h"

int* vb_credit_1_svc(char* acct_name, int amount, struct svc_req*) {
    return vb_change_balance(acct_name, amount, CREDIT);
}

int* vb_debit_1_svc(char* acct_name, int amount, struct svc_req*) {
    return vb_change_balance(acct_name, amount, DEBIT);
}

int* vb_change_balance(char* acct_name, int amount, int operation_mode) {
    static int ret = 0;
    int* res = nullptr;

    CLIENT* clnt;
    char server_name[10] = BANK1_ADDR;

    clnt = clnt_create(server_name, BANK1PROG, BANK1VERS, "tcp");

    if (clnt == NULL) {
        clnt_pcreateerror(server_name);
        ret = 1;
        return &ret;
    }

    if (operation_mode == CREDIT) {
        res = b1_credit_1(acct_name, amount, clnt);
    }
    else if (operation_mode == DEBIT) {
        res = b1_debit_1(acct_name, amount, clnt);
    }
    if (res== NULL) {
        clnt_perror(clnt, "Call to remote procedure failed.");
        ret = 1;
        return &ret;
    }

    if (*res == 0) {
        ret = 0;
    }
    else {
        ret = 1;
    }

    return &ret;
}

int* vb_transfer_1_svc(char* acct_1, char* acct_2, int amount, struct svc_req*) {
    static int result = 0;

    return &result;
}
