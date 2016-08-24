#!/bin/bash

make clean > out;
make > out;
mips-linux-gnu-gcc -S main_testcase.c > out;
