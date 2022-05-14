#!/bin/sh
echo Compilation
g++ ./main.cpp
echo Execution
./a.out
echo Ploting
python data_from_file.py
echo End
