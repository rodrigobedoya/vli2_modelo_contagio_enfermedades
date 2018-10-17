#ifndef CELL_H
#define CELL_H
#include <iostream>

class Cell
{
public:
	Cell();
	~Cell(){};
	void changeState();
	void setState(int new_state);
	int getState();
	int getDaysInfected();
	void setDaysInfected(int days_infected);
	void draw();
	void evaluate(int &death_count, bool &change);
	int getCureChance();
	int getInfectChance();

	void copy(Cell* copy)
	{
		this->state = copy->state;
		this->days_infected = copy->days_infected;
		this->infectChance = copy->infectChance;
		this->cureChance = copy->cureChance;
		this->resistance = copy->resistance;
	}

private:
	int state; //0 = healthy, 1 = infected, 2 = dead, 3=temporal_infected
	int days_infected;
	int infectChance;
	int cureChance;
	int resistance;
};

#endif