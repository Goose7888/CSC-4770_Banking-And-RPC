#!/bin/bash

echo "Credit an account on bank1 (b1_F24I25EM)"
./client.out localhost query b1_F24I25EM
./client.out localhost credit b1_F24I25EM 10
./client.out localhost query b1_F24I25EM

echo "Debit an account on bank1 (b1_214KPUFO)"
./client.out localhost query b1_214KPUFO
./client.out localhost debit b1_214KPUFO 100
./client.out localhost query b1_214KPUFO

echo "Demonstrate being unable to have a negtive balance"
./client.out localhost query b1_7T7BH9V2
./client.out localhost debit b1_7T7BH9V2 10
./client.out localhost query b1_7T7BH9V2

echo "Transfer from two accounts on bank1 (b1_86AZV0LU -> b1_F24I25EM)"
./client.out locahost query b1_86AZV0LU
./client.out locahost query b1_F24I25EM
./client.out locahost transfer b1_86AZV0LU b1_F24I25EM 50
./client.out locahost query b1_86AZV0LU
./client.out locahost query b1_F24I25EM

echo "Credit an account on bank2"
./client.out localhost query b2_4G69RJHD
./client.out localhost credit b2_4G69RJHD 10
./client.out localhost query b2_4G69RJHD

echo "Debit an account on bank2"
./client.out localhost query b2_S2HIPVSC
./client.out localhost debit b2_S2HIPVSC 100
./client.out localhost query b2_S2HIPVSC

echo "Demonstrate being unable to have a negtive balance"
./client.out localhost query b2_SRUKFK5E
./client.out localhost debit b2_SRUKFK5E 100
./client.out localhost query b2_SRUKFK5E

echo "Transfer from two accounts on bank2 "
./client.out localhost query b2_0B460I2N
./client.out localhost query b2_77YYHNWF
./client.out localhost transfer b2_0B460I2N b2_77YYHNWF 50
./client.out localhost query b2_0B460I2N
./client.out localhost b2_0B460I2N b2_77YYHNWF

echo "Transfer from bank1 to bank2"
./client.out localhost query b1_JTKAT98R
./client.out localhost query b2_41T81V4B
./client.out localhost transfer b1_JTKAT98R b2_41T81V4B 50
./client.out localhost query b1_JTKAT98R
./client.out localhost query b2_41T81V4B

echo "Transfer from bank2 to bank1"
./client.out localhost query b2_DORTN4FA
./client.out localhost query b1_R1GHOURB
./client.out localhost transfer b2_DORTN4FA b1_R1GHOURB 50
./client.out localhost query b2_DORTN4FA
./client.out localhost query b1_R1GHOURB
