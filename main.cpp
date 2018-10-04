#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#include "cell.h"
#include "cell_grid.h"
#include <iostream>


const sf::Vector2f window_size(800,600);
const sf::Vector2f number_of_cells(10,10);
const sf::Vector2f cell_size(window_size.x/number_of_cells.x,window_size.y/number_of_cells.y);
bool click_pressed = false;
bool click_pressed_r = false;

sf::Vector2i getClickedCell(sf::RenderWindow &window, sf::Vector2i mouse_pos);

int main()
{
    CellGrid Grid(number_of_cells,cell_size);
    
    /*
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(window_size.x,window_size.y), "SFML window");
    sf::RectangleShape white_background(window_size);

    
    while (window.isOpen())
    {

        //Change state when mouse click has been released
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            click_pressed = true;
        if(click_pressed && !sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            click_pressed = false;
            Cell *clicked= Grid.getClickedCell(sf::Mouse::getPosition(window));
            clicked->changeState();
            Grid.run();
        }      

        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch(event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    return 0;
                    
                case sf::Event::KeyPressed:
                    Grid.run();
                    std::cout << "a" << std::endl;
            }
        }
        // Clear screen
        window.clear();
        window.draw(white_background);
        
        Grid.draw(window);

        // Update the window
        window.display();
    }*/
    return EXIT_SUCCESS;
}

