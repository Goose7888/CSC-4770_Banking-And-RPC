program BANK2PROG {
    version BANK2VERS {
        int B2_credit(string, int) = 1;
        int B2_debit(string, int) = 2;
        int B2_acct_exists(string) = 3;
    } = 1;
} = 0x200024;
