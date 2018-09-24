#!/bin/bash
g++ -c -std=c++11 main.cpp cell.cpp
g++ main.o cell.cpp -o run-model -lsfml-graphics -lsfml-window -lsfml-system 
$SHELL