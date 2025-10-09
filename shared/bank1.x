const MAXLENGTH = 156;

struct b1_account {
    string id<MAXLENGTH>;
    int balance;
    int errorcode;
};

program BANK1PROG {
    version BANK1VERS {
        int B1_credit(string, int) = 1;
        int B1_debit(string, int) = 2;
        b1_account B1_acct_lookup(string) = 3;
    } = 1;
} = 0x200023;
