#include "cell.h"
#include <iostream>
Cell::Cell(sf::Vector2f cell_size):
	sf::RectangleShape(cell_size),
	state(0),
	days_infected(0)
{
	this->setOutlineColor(sf::Color::Black);
	this->setOutlineThickness(5);
}

void Cell::changeState()
{
	if(state==0)
	{
		this->setFillColor(sf::Color::Red);
		state = 1;
		std::cout << " is now infected";
	}
	else
	{
		this->setFillColor(sf::Color::White);
		state = 0;
		std::cout << " is not infected anymore";
	}
	std::cout << std::endl;
}

void Cell::setState(int new_state)
{
	state = new_state;
}

int Cell::getState()
{
	return state;
}

void Cell::draw(sf::RenderWindow &window)
{
	if(state == 3)
	{
		state = 1;
		this->setFillColor(sf::Color::Red);
	}

	window.draw(*this);
}

int Cell::getDaysInfected()
{
	return days_infected;
}


void Cell::evaluate()
{
	if(state == 0)
		days_infected = 0;

	if(days_infected > 6)
	{
		state=2;
		this->setFillColor(sf::Color::Black);
	}

	if(state == 1)
		days_infected+=1;

	
}