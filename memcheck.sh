#!/bin/bash -ex
g++ -g main.cpp 
valgrind --leak-check=full ./a.out
