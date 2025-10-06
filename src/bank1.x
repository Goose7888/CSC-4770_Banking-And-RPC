const MAXACCTLEN = 255;

struct bank1_account {
    int errorcode;
    string acctnumber<MAXACCTLEN>;
    int balance;
};

struct bank1_params {
    string acctnumber<MAXACCTLEN>;
    int amount;
};

struct bank1_transfer_params {
    string acctnumber1<MAXACCTLEN>;
    string acctnumber2<MAXACCTLEN>;
    int amount;
};

program BANKPROG1 {
    version BANKVERS {
        int BANK1_CREDIT(string) = 1;
        int BANK1_DEBIT(string) = 2;
        account BANK1_ACCT_LOOKUP(string) = 3;
        int BANK1_INITIALIZE_BANK() = 4;
    } = 1;
} = 0x200023;

program BANKPROG2 {
    version BANKVERS {
        int BANK1_CREDIT(string) = 1;
        int BANK1_DEBIT(string) = 2;
        account BANK1_ACCT_LOOKUP(string) = 3;
        int BANK1_INITIALIZE_BANK() = 4;
    } = 1;
} = 0x200024;
