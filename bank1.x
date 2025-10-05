const MAXACCTLEN = 255;

struct account {
    int errorcode;
    string acctnumber<MAXACCTLEN>;
    int balance;
};

program BANKPROG1 {
    version BANKVERS {
        int CREDIT(string) = 1;
        int DEBIT(string) = 2;
        account ACCT_LOOKUP(string) = 4;
    } = 1;
} = 0x200023;
