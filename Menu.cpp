#include "Menu.h"
#include <iostream>

Menu::Menu() : win(sf::VideoMode(250, 350), "Menu", sf::Style::Default)
{
    win.setPosition(sf::Vector2i(50,80));
    level1.setSize(sf::Vector2f(130, 66));
    level2.setSize(sf::Vector2f(130, 66));
    level3.setSize(sf::Vector2f(130, 66));

    level1.setFillColor(sf::Color::Green);
    level2.setFillColor(sf::Color::Blue);
    level3.setFillColor(sf::Color::Red);

    level1.setOutlineThickness(4);
    level2.setOutlineThickness(4);
    level3.setOutlineThickness(4);

    level1.setOutlineColor(sf::Color(0, 100, 0));
    level2.setOutlineColor(sf::Color(0, 0, 100));
    level3.setOutlineColor(sf::Color(100, 0, 0));

    level1.setPosition(sf::Vector2f(60, 30));
    level2.setPosition(sf::Vector2f(60, 137));
    level3.setPosition(sf::Vector2f(60, 244));
}

int Menu::choice()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
        if ((sf::Mouse::getPosition().x < 246 && sf::Mouse::getPosition().x > 117)
            && (sf::Mouse::getPosition().y < 224 && sf::Mouse::getPosition().y > 156))
            {
               return 1;
            }
        else if ((sf::Mouse::getPosition().x < 246 && sf::Mouse::getPosition().x > 117)
            && (sf::Mouse::getPosition().y < 331 && sf::Mouse::getPosition().y > 268))
            {
                return 2;
            }
        else if ((sf::Mouse::getPosition().x < 246 && sf::Mouse::getPosition().x > 11)
            && (sf::Mouse::getPosition().y < 439 && sf::Mouse::getPosition().y > 375))
            {
                return 3;
            }
        else return 0;
    }
    else return 0;
}


