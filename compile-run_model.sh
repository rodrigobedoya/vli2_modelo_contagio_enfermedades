#!/bin/bash
g++ -c main.cpp cell.cpp
g++ main.o cell.cpp -o run-model -lsfml-graphics -lsfml-window -lsfml-system 
./run-model
$SHELL