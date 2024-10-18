#!/bin/bash

#create folder build while not exist
mkdir -p build

#build
# -pthread: create thread
gcc -o ./build/mt mul_thread.c -pthread