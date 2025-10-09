/* virtual_bank.cpp */

#include "virtual_bank.h"
#include "rpc/clnt.h"

int* vb_credit_1_svc(char* acct, int amount, struct svc_req*) {
    static int ret = 0;
    std::cout << "IM REALLY LOUD!!!!" << std::endl;

    CLIENT* clnt;
    int* result;
    char server_name[10] = "localhost";

    clnt = clnt_create(server_name, BANK1PROG, BANK1VERS, "tcp");

    if (clnt == NULL) {
        clnt_pcreateerror(server_name);
        ret = 1;
        return &ret;
    }

    account* res = b1_acct_lookup_1(acct, clnt);
    if (res== NULL) {
        clnt_perror(clnt, "Call to remote procedure failed.");
    }
    else {
        std::cout << res->errorcode << res->id << " " << res->balance << std::endl;
    }

    return &ret;
}
int* vb_debit_1_svc(char* acct, int amount, struct svc_req*) {
    static int result = 0;

    return &result;
}
int* vb_transfer_1_svc(char* acct_1, char* acct_2, int amount, struct svc_req*) {
    static int result = 0;

    return &result;
}

// Like python's string `split` method
std::vector<std::string> split(const std::string &input, const std::string &delimiter){
    size_t pos = 0;
    size_t lpos = 0;
    size_t dlen = delimiter.length();

    std::vector<std::string> ret;

    // push_back substring before every instance of `delimiter`
    while ((pos = input.find(delimiter, lpos)) != std::string::npos) {
        ret.push_back(input.substr(lpos, pos - lpos));
        lpos = pos + dlen;
    }
    // push_back the remainder of the string
    ret.push_back(input.substr(lpos, input.length()));

    return ret;
}
