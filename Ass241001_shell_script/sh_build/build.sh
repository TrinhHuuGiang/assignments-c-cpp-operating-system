#!/bin/bash
#Please run it first time using the check_empty_file (CEF)
#create folder build while not exist
mkdir -p build

g++ -o ./build/order order.cpp

#set execute mode
chmod +x ./build/order