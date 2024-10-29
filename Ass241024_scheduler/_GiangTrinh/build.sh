#!/bin/bash

#create folder build while not exist
mkdir -p build

#build
# -pthread: create thread
gcc -o ./build/scheduler main.c delay_ms.c mapping.c process_handler.c SJN_linkedlist.c -lrt

#export and overwrite to build/output.txt
./build/scheduler > ./build/output.txt