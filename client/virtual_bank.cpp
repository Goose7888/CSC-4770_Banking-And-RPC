#include "virtual_bank.hpp"
#include "vbank.h"

int* credit_1_svc(char** inputRaw, struct svc_req* rqstp) {
    static int result;

    std::string input = *inputRaw;

    std::vector<std::string> params = split(input, " ");

    if (params.size() != 2) {
        result = 0;
    }
    else {
        result = 1;
    }

    return &result;
};

int* debit_1_svc(char** inputRaw, struct svc_req* rqstp) {
    static int result;

    std::string input = *inputRaw;

    std::vector<std::string> params = split(input, " ");

    if (params.size() != 2) {
        result = 0;
    }
    else {
        result = 1;
    }

    result = 1;
    return &result;
}

int* transfer_1_svc(char** inputRaw, struct svc_req* rqstp) {
    static int result;

    std::string input = *inputRaw;

    std::vector<std::string> params = split(input, " ");

    if (params.size() != 3) {
        result = 0;
    }
    else {
        result = 1;
    }

    result = 1;
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
