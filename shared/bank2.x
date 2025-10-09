const MAXLENGTH = 156;

struct b2_account {
    string id<MAXLENGTH>;
    int balance;
    int errorcode;
};

program BANK2PROG {
    version BANK2VERS {
        int B2_credit(string, int) = 1;
        int B2_debit(string, int) = 2;
        b2_account B2_acct_lookup(string) = 3;
    } = 1;
} = 0x200024;
