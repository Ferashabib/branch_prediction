## UID: 905744996

## Pipe Up

In this assignment, we try to recreate the pipe operator in shell. This program should function exactly like the pipe operator (with the exception of no flags)

## Building

Just use make
OR
use gcc -o name pipe.c

## Running

*Example 1*

cs111@cs111 Downloads/lab1 (main !%) » ./pipe ls cat     

Makefile

pipe

pipe.c

pipe.o

README.md

test_lab1.py

cs111@cs111 Downloads/lab1 (main !%) » ls | cat          

Makefile

pipe

pipe.c

pipe.o

README.md

test_lab1.py

*Example 2*

cs111@cs111 Downloads/lab1 (main !%) » ./pipe ls wc 

      6       6      51

cs111@cs111 Downloads/lab1 (main !%) » ls | wc     

      6       6      51



## Cleaning up

make clean
or manually use rm
