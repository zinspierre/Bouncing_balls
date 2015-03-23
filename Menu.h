#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Menu
{
private:
    sf::RectangleShape level1;
    sf::RectangleShape level2;
    sf::RectangleShape level3;

public:
    sf::RenderWindow win;
    Menu();
    ~Menu(){};

    int choice();
    sf::RectangleShape getLevel1() const {return level1;};
    sf::RectangleShape getLevel2() const {return level2;};
    sf::RectangleShape getLevel3() const {return level3;};

};


#endif // MENU_H_INCLUDED
