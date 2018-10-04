#ifndef CELLGRID_H
#define CELLGRID_H
#include "cell.h"
#include <vector>

class CellGrid
{
public:
	CellGrid(float numberX, float numberY);
	~CellGrid();
	Cell* at(int posX,int posY);
	void draw();
	bool isDead();
	int getDeathCount();
	std::vector<Cell*> surroundingCells(int posX,int posY);
	void run();
	void summary();
private:
	float number_of_cellsX;
	float number_of_cellsY;
	bool dead;
	int death_count;
	std::vector<std::vector<Cell*> > grid;
};

#endif