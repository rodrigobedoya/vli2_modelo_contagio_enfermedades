#include "cell.h"

Cell::Cell(sf::Vector2f cell_size):
	sf::RectangleShape(cell_size),
	healthy(true)
{

}


void Cell::changeState()
{
	if(healthy)
	{
		this->setFillColor(sf::Color::Black);
		healthy = false;
	}
	else
	{
		this->setFillColor(sf::Color::White);
		healthy = true;
	}
}

void Cell::setState(bool state)
{
	healthy = state;
}

bool Cell::isHealthy()
{
	return healthy;
}