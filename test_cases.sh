#!/bin/bash

echo "Credit an account on bank1 (b1_F24I25EM)"
# Query account to show before
./client.out credit b1_F24I25EM 10
# Query account to show after

echo "Debit an account on bank1 (b1_214KPUFO)"
# Query
./client.out debit b1_214KPUFO 100
# Query

echo "Demonstrate being unable to have a negtive balance"
# Query
./client.out debit b1_7T7BH9V2 10
# Query

echo "Transfer from two accounts on bank1 (b1_86AZV0LU -> b1_F24I25EM)"
# Query both
./client.out transfer b1_86AZV0LU b1_F24I25EM 50
# Query both


echo "Credit an account on bank2 ()"
# Query account to show before
./client.out credit  10
# Query account to show after

echo "Debit an account on bank2 ()"
# Query
./client.out debit  100
# Query

echo "Demonstrate being unable to have a negtive balance"
# Query
./client.out debit  10
# Query

echo "Transfer from two accounts on bank2 ( -> )"
# Query both
./client.out transfer   50
# Query both
