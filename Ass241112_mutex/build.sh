#!/bin/bash

#create folder build while not exist
mkdir -p build

g++ -o ./build/mutex mutex_pthread.cpp