#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

const sf::Vector2f window_size(800,600);
const sf::Vector2f number_of_cells(10,10);
const sf::Vector2f cell_size(window_size.x/number_of_cells.x,window_size.y/number_of_cells.y);
const sf::Vector2f start(0,0);

int main()
{
    // Create the main window
    sf::RenderWindow window(sf::VideoMode(window_size.x,window_size.y), "SFML window");
    sf::RectangleShape white_background(window_size);

    sf::RectangleShape *cell_grid[int(number_of_cells.x)][int(number_of_cells.y)];
    
    for(int i = 0;i < number_of_cells.y;i++)
    {
        for(int j = 0; j < number_of_cells.x;j++)
        {
            //do something
            cell_grid[i][j] = new sf::RectangleShape(cell_size);
            cell_grid[i][j]->setOutlineColor(sf::Color::Black);
            cell_grid[i][j]->setOutlineThickness(5);
            cell_grid[i][j]->setPosition(sf::Vector2f(cell_size.x*j,cell_size.y*i));
        }
    }

    while (window.isOpen())
    {
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