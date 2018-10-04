#include "cell.h"
#include <iostream>
Cell::Cell():
	state(0),
	days_infected(0)
{
	infectChance = 60;
	cureChance = 15;
	resistance = 2;
}

void Cell::changeState()
{
	if(state==0)
	{
		state = 1;
		std::cout << " is now infected";
	}
	else
	{
		state = 0;
		std::cout << " is not infected anymore";
	}
	std::cout << std::endl;
}

void Cell::setState(int new_state)
{
	state = new_state;
}

void Cell::setDaysInfected(int days_infected)
{
	this->days_infected = days_infected; 
}

int Cell::getState()
{
	return state;
}

void Cell::draw()
{
	std::cout << state << " ";
}

int Cell::getDaysInfected()
{
	return days_infected;
}


void Cell::evaluate(int &death_count, bool &change)
{
	if(state == 1)
	{
		change = true;
		if(days_infected > resistance)
		{
			state=2;
			death_count++;
		}
		else
			days_infected+=1;
	}
	else if(state == 3)
	{	
		change = true;
		state=1;
	}
	
}

int Cell::getCureChance()
{
	return cureChance;
}

int Cell::getInfectChance()
{
	return infectChance;
}