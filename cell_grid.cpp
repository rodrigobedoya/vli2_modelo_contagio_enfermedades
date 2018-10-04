#include "cell_grid.h"
#include <iostream>
#include <stdlib.h>

CellGrid::CellGrid(sf::Vector2f numberCells,sf::Vector2f cellSize):
	number_of_cells(numberCells),
	cell_size(cellSize)
{
	grid.reserve(number_of_cells.y);
	Cell base(cellSize);
	std::vector<Cell> cell_row(number_of_cells.x,base);
	/*for(int i = 0; i < number_of_cells.y;i++)
	{
		grid.push_back(cell_row);
	}*/	
	for(int i = 0;i < number_of_cells.x;i++)
    {
    	std::vector<Cell> newV;
    	newV.clear();
    	newV.reserve(number_of_cells.x);
        for(int j = 0; j < number_of_cells.y;j++)
        {
            Cell *newCell = new Cell(cell_size);
            newCell->setPosition(sf::Vector2f(cell_size.x*j,cell_size.y*i));
            newV.push_back(*newCell);
        }
        grid.push_back(newV);
    }
}

Cell CellGrid::at(int posX, int posY)
{
	return grid[posX][posY];
}

void CellGrid::draw(sf::RenderWindow &window)
{
	for(int i = 0;i < number_of_cells.y;i++)
        {
            for(int j = 0; j < number_of_cells.x;j++)
            {
                at(i,j).draw(window);
            }
        }
}

Cell* CellGrid::getClickedCell(sf::Vector2i mouse_pos)
{
	int column,row;
    
    for(int i = 0; i < number_of_cells.x;i++)
    {
        if(mouse_pos.x< cell_size.x*(i+1))
        {
            column = i;
            break;
        }
    }
    for(int i = 0; i < number_of_cells.y;i++)
    {
        if(mouse_pos.y < cell_size.y*(i+1))
        {
            row = i;
            break;
        }    
    }
    std::cout << row << "," << column;
    return &grid[row][column];
}

std::vector<Cell*> CellGrid::surroundingCells(int posX,int posY)
{
	std::vector<Cell*> environment;
	if (posY != 0) //left
	{
		if(grid[posX][posY-1].getState() == 0)
			environment.push_back(&grid[posX][posY-1]);
	}

	if (posY != number_of_cells.y-1) //right
	{
		if(grid[posX][posY+1].getState() == 0)
			environment.push_back(&grid[posX][posY+1]);
	}
	if (posX != 0) //above 
	{
		if(grid[posX-1][posY].getState() == 0)
			environment.push_back(&grid[posX-1][posY]);
	}

	if (posX != number_of_cells.x-1) //below
	{
		if(grid[posX+1][posY].getState() == 0)
			environment.push_back(&grid[posX+1][posY]);
	}
	return environment;

}

void CellGrid::run()
{
	for(int i = 0; i < number_of_cells.x;i++)
	{
		for(int j = 0; j < number_of_cells.y;j++)
		{
			grid[i][j].evaluate();
			if(grid[i][j].getState() == 1)
			{
				int cured = rand()%100;
				if(cured > 98)
				{
					grid[i][j].setState(0);
					continue;
				}

				std::vector<Cell*> possibleInfections = surroundingCells(i,j);
				for(std::vector<Cell*>::iterator it=possibleInfections.begin(); it!=possibleInfections.end(); ++it)
				{
					int prob = rand()%100;
					if(prob > 40)
					{
						(*it)->setState(3);
					}
				}
			}
		}
	}	
}