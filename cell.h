#ifndef CELL_H
#define CELL_H

#include <SFML/Graphics.hpp>

class Cell:public sf::RectangleShape
{
public:
	Cell(sf::Vector2f cell_size);

	void changeState();
	void setState(int new_state);
	int getState();
	int getDaysInfected();
	void draw(sf::RenderWindow &window);
	void evaluate();
private:
	int state; //0 = healthy, 1 = infected, 2 = dead, 3=temporal_infected
	int days_infected;
};

#endif