#!/bin/bash
g++ -std=c++11 *.cpp -o hw1.ex
./hw1.ex < $1 > $2
rm hw1.ex