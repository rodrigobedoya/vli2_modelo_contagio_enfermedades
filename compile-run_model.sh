#!/bin/bash
g++ -c -std=c++11 main.cpp cell.cpp cell_grid.cpp
g++ main.o cell.cpp cell_grid.cpp -o run-model -lsfml-graphics -lsfml-window -lsfml-system 
./run-model
$SHELL