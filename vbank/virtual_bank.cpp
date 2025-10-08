/* virtual_bank.cpp */

#include "virtual_bank.h"

int* vb_credit_1_svc(char* acct, int amount, struct svc_req*) {
    return 0;
}
int* vb_debit_1_svc(char* acct, int amount, struct svc_req*) {
    return 0;
}
int* vb_transfer_1_svc(char* acct_1, char* acct_2, int amount, struct svc_req*) {
    return 0;
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
