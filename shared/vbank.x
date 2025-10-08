program VBANKPROG {
    version VBANKVERS {
        int VB_CREDIT(string, int) = 1;
        int VB_DEBIT(string, int) = 2;
        int VB_TRANSFER(string, string, int) = 3;
    } = 1;
} = 0x200022;
