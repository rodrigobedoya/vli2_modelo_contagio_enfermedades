#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "cell.h"

#include <iostream>


const sf::Vector2f window_size(800,600);
const sf::Vector2f number_of_cells(10,10);
const sf::Vector2f cell_size(window_size.x/number_of_cells.x,window_size.y/number_of_cells.y);
const sf::Vector2f start(0,0);
bool click_pressed = false;

sf::Vector2i getClickedCell(sf::RenderWindow &window, sf::Vector2i mouse_pos);

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(window_size.x,window_size.y), "SFML window");
    sf::RectangleShape white_background(window_size);

    Cell *cell_grid[int(number_of_cells.x)][int(number_of_cells.y)];
    
    for(int i = 0;i < number_of_cells.y;i++)
    {
        for(int j = 0; j < number_of_cells.x;j++)
        {
            cell_grid[i][j] = new Cell(cell_size);
            cell_grid[i][j]->setOutlineColor(sf::Color::Black);
            cell_grid[i][j]->setOutlineThickness(5);
            cell_grid[i][j]->setPosition(sf::Vector2f(cell_size.x*j,cell_size.y*i));
        }
    }

    while (window.isOpen())
    {

        //Change state when mouse click has been released
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            click_pressed = true;
        if(click_pressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            click_pressed = false;
            //std::cout << sf::Mouse::getPosition(window).x << "," << sf::Mouse::getPosition(window).y << std::endl;
            sf::Vector2i clicked_cell_pos = getClickedCell(window,sf::Mouse::getPosition(window));
            cell_grid[clicked_cell_pos.x][clicked_cell_pos.y]->changeState();
        }


        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window: exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear();
        window.draw(white_background);
        
        for(int i = 0;i < number_of_cells.y;i++)
        {
            for(int j = 0; j < number_of_cells.x;j++)
            {
                window.draw(*cell_grid[i][j]);
            }
        }

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}


sf::Vector2i getClickedCell(sf::RenderWindow &window, sf::Vector2i mouse_pos)
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
    return sf::Vector2i(row,column);
}