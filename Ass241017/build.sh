#!/bin/bash

#create folder build while not exist
mkdir -p build

#build include Real-time extensions library -lrt
gcc -o ./build/sharemem sharemem.c -lrt