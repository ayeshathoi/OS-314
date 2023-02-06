#!/bin/bash
# script takes 2 arguments that are given to the barber-shop program
# $1 = number of customers
# $2 = number of chairs

gcc -o barber-shop-zemaphore barber-shop-zemaphore.c -lpthread
./barber-shop-zemaphore $1 $2 
# ./barber-shop $1 $2 $3 $4 > output 
# awk -f check.awk MAX=$1 output
