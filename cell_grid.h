#ifndef CELLGRID_H
#define CELLGRID_H
#include "cell.h"
#include <vector>

class CellGrid
{
public:
	CellGrid(const sf::Vector2f number_of_cells,const sf::Vector2f cell_size);

	Cell at(int posX,int posY);
	void draw(sf::RenderWindow &window);
	Cell* getClickedCell(sf::Vector2i mouse_pos);

	std::vector<Cell*> surroundingCells(int posX,int posY);
	void run();
private:
	sf::Vector2f number_of_cells;
	sf::Vector2f cell_size;

	std::vector<std::vector<Cell> > grid;
};

#endif