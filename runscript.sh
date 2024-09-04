#!/bin/bash
rm -f *.o *.out
gcc -c encrypt.c -o encrypt.o
gcc banking_system.c encrypt.o -o ./bank.out
