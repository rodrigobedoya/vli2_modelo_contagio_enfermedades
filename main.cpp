#include <iostream>
#include <stdlib.h>

#include "cell_grid.h"

const int numberX = 10;
const int numberY = 10;
bool click_pressed = false;
bool click_pressed_r = false;

int main()
{
	srand((unsigned)time(0));
    int startX,startY,infect;

    std::cout << "Infected: " << std::endl;
    std::cin >> infect;

    CellGrid Grid(numberX,numberY);
    for(int i = 0; i< infect; i++)
    {
    	startX = rand()%numberX;
    	startY = rand()%numberY;
    	Grid.at(startX,startY)->setState(1);
    }

        
    std::cout << "INICIO: "<<std::endl;
    Grid.draw();

    std::cout << "Inserte el numero de repeticiones: ";
    
    long int rep;
    std::cin >> rep;

    for(int i = 0; i < rep; i++)
    {
    	if(Grid.isDead())
    	{
    		break;
    	}
    	std::cout << "DIA " << i+1 << std::endl;
    	Grid.run();
    }
    
    std::cout << "DIA " << rep << std::endl;
    Grid.run();	
    Grid.summary();
    return 0;
}

