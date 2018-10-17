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
	void summary(std::vector<int> &dead, std::vector<int> &alive);

	void clear()
	{
		for(int i = 0; i < number_of_cellsX;i++)
		{
			for (int j = 0; j < number_of_cellsY;j++)
			{
				delete grid[i][j];
			}
		}
	}

	void copy(CellGrid* newc)
	{
		for(int i = 0; i < number_of_cellsX;i++)
		{
			for(int j = 0; j < number_of_cellsY;j++)
			{
				Cell* copy_cell = newc->grid[i][j];
				grid[i][j] = new Cell;
				grid[i][j]->copy(copy_cell);
			}
		}
		return;
	}

private:

	float number_of_cellsX;
	float number_of_cellsY;
	bool dead;
	int death_count;
	std::vector<std::vector<Cell*> > grid;
};

#endif