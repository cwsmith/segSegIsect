#!/bin/bash -ex
g++ -g -fprofile-arcs -ftest-coverage main.cpp 
./a.out
gcov main.cpp
