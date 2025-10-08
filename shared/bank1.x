program BANK1PROG {
    version BANK1VERS {
        int B1_credit(string, int) = 1;
        int B1_debit(string, int) = 2;
        int B1_acct_exists(string) = 3;
    } = 1;
} = 0x200023;
