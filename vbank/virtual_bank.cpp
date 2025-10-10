/* virtual_bank.cpp */

#include "virtual_bank.h"

int* vb_credit_1_svc(char* acct_name, int amount, struct svc_req*) {
    return vb_change_balance(acct_name, amount, CREDIT);
}

int* vb_debit_1_svc(char* acct_name, int amount, struct svc_req*) {
    return vb_change_balance(acct_name, amount, DEBIT);
}

int* vb_transfer_1_svc(char* acct_1, char* acct_2, int amount, struct svc_req*) {
    static int ret = 0;
    int* result = nullptr;

    result = vb_change_balance(acct_1, amount, DEBIT);
    if (result == NULL) {
        ret = 1;
        return &ret;
    }
    else if (*result != 0) {
        ret = 1;
        return &ret;
    }

    result = vb_change_balance(acct_2, amount, CREDIT);
    if (result == NULL) {
        ret = 1;
        return &ret;
    }
    else if (*result != 0) {
        ret = 1;
        return &ret;
    }

    return &ret;
}

int* vb_change_balance(char* acct_name, int amount, int operation_mode) {
    static int ret = 0;
    int acct_location = get_acct_location(acct_name);

    if (change_balance(acct_name, amount, operation_mode, acct_location) == false) {
        ret = 1;
        return &ret;
    }

    ret = 0;
    return &ret;
}

// returns whether there was success in changing the account's balance
bool change_balance(char* acct_name, int amount, int operation_mode, int bank_location) {
    CLIENT* clnt;
    int* result;
    char server_name[31] = "";
    bool ret = false;

    if (bank_location == BANK1) {
        strcpy(server_name, BANK1_ADDR);
        clnt = clnt_create(server_name, BANK1PROG, BANK1VERS, "tcp");
    }
    else if (bank_location == BANK2) {
        strcpy(server_name, BANK2_ADDR);
        clnt = clnt_create(server_name, BANK2PROG, BANK2VERS, "tcp");
    }
    else {
        std::cerr << "Invalid bank selected!" << std::endl;
        return false;
    }

    if (clnt == NULL) {
        clnt_pcreateerror(server_name);
        return false;
    }

    if (operation_mode == CREDIT) {
        if (bank_location == BANK1) {
            result = b1_credit_1(acct_name, amount, clnt);
        }
        else if (bank_location == BANK2) {
            result = b2_credit_1(acct_name, amount, clnt);
        }
    }
    else if (operation_mode == DEBIT) {
        if (bank_location == BANK1) {
            result = b1_debit_1(acct_name, amount, clnt);
        }
        else if (bank_location == BANK2) {
            result = b2_debit_1(acct_name, amount, clnt);
        }
    }

    if (*result == 0) {
        ret = true;
    }
    else {
        ret = false;
    }

    return ret;
}

// just returns true if acct exists
bool get_acct(char* acct_name, int bank_location) {
    CLIENT* clnt;
    char server_name[31] = "";

    if (bank_location == BANK1) {
        strcpy(server_name, BANK1_ADDR);
        clnt = clnt_create(server_name, BANK1PROG, BANK1VERS, "tcp");
    }
    else if (bank_location == BANK2) {
        strcpy(server_name, BANK2_ADDR);
        clnt = clnt_create(server_name, BANK2PROG, BANK2VERS, "tcp");
    }
    else {
        std::cerr << "Invalid bank selected!" << std::endl;
        return false;
    }

    if (clnt == NULL) {
        clnt_pcreateerror(server_name);
        return false;
    }

    b1_account* b1_res = b1_acct_lookup_1(acct_name, clnt);
    if (b1_res->errorcode == 0) {
        clnt_destroy(clnt);
        return true;
    }

    clnt_destroy(clnt);
    return false;
}

// returns acct_location
int get_acct_location(char* acct_name) {
    int acct_location;
    if (get_acct(acct_name, BANK1)) {
        acct_location = BANK1;
    }
    else if (get_acct(acct_name, BANK2)) {
        acct_location = BANK2;
    }
    else {
        acct_location = NO_BANK;
    }
    return acct_location;
}
