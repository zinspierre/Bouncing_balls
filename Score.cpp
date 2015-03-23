#include "Score.h"
#include <iostream>
#include <fstream>
#include <sstream>


std::string to_string2(float value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}

Score::Score() : scoreWin(sf::VideoMode(250, 210), "Score", sf::Style::Default)
{
    scoreWin.setPosition(sf::Vector2i(50, 470));
    font.loadFromFile("arial.ttf");

    bestScore1.setCharacterSize(40);
    bestScore1.setFont(font);
    bestScore1.setColor(sf::Color::Green);
    bestScore1.setPosition(55, 20);

    bestScore2.setCharacterSize(40);
    bestScore2.setFont(font);
    bestScore2.setColor(sf::Color::Blue);
    bestScore2.setPosition(55, 80);

    bestScore3.setCharacterSize(40);
    bestScore3.setFont(font);
    bestScore3.setColor(sf::Color::Red);
    bestScore3.setPosition(55, 140);
}

float Score::importScore(int level)
{
    std::ifstream file("score.txt");
    float score1;
    float score2;
    float score3;
    if (file.is_open())
    {
        file >> score1 >> score2 >> score3;
        file.close();
    }
    bestScore1.setString(to_string2(score1));
    bestScore2.setString(to_string2(score2));
    bestScore3.setString(to_string2(score3));
    bestLvl1 = score1;
    bestLvl2 = score2;
    bestLvl3 = score3;

    switch(level)
    {
        case 1 : return score1;
        break;
        case 2 : return score2;
        break;
        case 3 : return score3;
        break;
    }
}

void Score::exportScore(std::string best, int level)
{
    std::ofstream file("score.txt");
    if (file.is_open())
    {
        if (level == 1)
        {
            file << best << std::endl;
            file << to_string2(bestLvl2) << std::endl;
            file << to_string2(bestLvl3);
        }
        else if (level == 2)
        {
            file << to_string2(bestLvl1) << std::endl;
            file << best;
            file << to_string2(bestLvl3);
        }
        else if (level == 3)
        {
            file << to_string2(bestLvl1) << std::endl;
            file << to_string2(bestLvl2) << std::endl;
            file << best;
        }
        file.close();
    }
}
