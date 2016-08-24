#!/bin/bash

make clean > out;
make > out;
mips-linux-gnu-gcc -S test_case.c > out;
