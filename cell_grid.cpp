#include "cell_grid.h"
#include <iostream>
#include <stdlib.h>

CellGrid::CellGrid(float numberX, float numberY):
	number_of_cellsX(numberX),
	number_of_cellsY(numberY),
	dead(false),
	death_count(0)
{
	grid.reserve(number_of_cellsY);
	for(int i = 0;i < number_of_cellsX;i++)
    {
    	std::vector<Cell*> newV;
    	newV.clear();
    	newV.reserve(number_of_cellsX);
        for(int j = 0; j < number_of_cellsY;j++)
        {
            Cell *newCell = new Cell;
            newV.push_back(newCell);
        }
        grid.push_back(newV);
    }
}

CellGrid::~CellGrid()
{
	for(int i = 0;i < number_of_cellsX;i++)
    {
        for(int j = 0; j < number_of_cellsY;j++)
        {
        	delete grid[i][j];
        }
    }	
}

Cell* CellGrid::at(int posX, int posY)
{
	return grid[posX][posY];
}

void CellGrid::draw()
{
	for(int i = 0;i < number_of_cellsY;i++)
        {
            for(int j = 0; j < number_of_cellsX;j++)
            {
                grid[i][j]->draw();
            }
            std::cout << std::endl;
        }
}

int CellGrid::getDeathCount()
{
	return death_count;
}

std::vector<Cell*> CellGrid::surroundingCells(int posX,int posY)
{
	bool left_side = true, right_side = true, upper_side = true, down_side = true; 
	std::vector<Cell*> environment;
	if (posY != 0) //left
	{
		if(grid[posX][posY-1]->getState() == 0)
			environment.push_back(grid[posX][posY-1]);
		left_side = false;
	}

	if (posY != number_of_cellsY-1) //right
	{
		if(grid[posX][posY+1]->getState() == 0)
			environment.push_back(grid[posX][posY+1]);
		right_side = false;
	}
	if (posX != 0) //above 
	{
		if(grid[posX-1][posY]->getState() == 0)
			environment.push_back(grid[posX-1][posY]);
		upper_side = false;
	}

	if (posX != number_of_cellsX-1) //below
	{
		if(grid[posX+1][posY]->getState() == 0)
			environment.push_back(grid[posX+1][posY]);
		down_side = false;
	}


	return environment;

}

bool CellGrid::isDead()
{
	return dead;
}

void CellGrid::run()
{
	bool change = false;
	for(int i = 0; i < number_of_cellsX;i++)
	{
		for(int j = 0; j < number_of_cellsY;j++)
		{
			grid[i][j]->evaluate(death_count,change);
						
			if(grid[i][j]->getState() == 1)
			{
				//CURE INFECETD CELLS
				int cured = rand()%100;
				if(cured+1 < grid[i][j]->getCureChance())
				{
					grid[i][j]->setState(0);
					grid[i][j]->setDaysInfected(0);
					change = true;
					continue;
				}

				//INFECT SURROUNDING CELLS
				std::vector<Cell*> possibleInfections = surroundingCells(i,j);
				for(std::vector<Cell*>::iterator it=possibleInfections.begin(); it!=possibleInfections.end(); ++it)
				{
					int infected = rand()%100;
					if(infected+1 < grid[i][j]->getInfectChance())
					{
						(*it)->setState(3);
						change = true;
					}
				}
			}
		}
	}
	if(death_count == number_of_cellsX*number_of_cellsY || !change)
		dead = true;
}

void CellGrid::summary(std::vector<int> &dead, std::vector<int> &alive)
{
	int alive_count = number_of_cellsX*number_of_cellsY - death_count;
	dead.push_back(death_count);
    alive.push_back(alive_count);
}