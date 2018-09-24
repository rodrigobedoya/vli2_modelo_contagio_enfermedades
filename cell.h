#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

class Cell:public sf::RectangleShape
{
public:
	Cell(sf::Vector2f cell_size);

	void changeState();
	void setState(bool state);
	bool isHealthy();

private:
	bool healthy;
};

#endif