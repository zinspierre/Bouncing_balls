#ifndef SCORE_H_INCLUDED
#define SCORE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Score
{
private:
    sf::Text bestScore1;
    sf::Text bestScore2;
    sf::Text bestScore3;
    sf::Font font;
    float bestLvl1;
    float bestLvl2;
    float bestLvl3;
public:
    sf::RenderWindow scoreWin;
    Score();
    ~Score(){};
    float importScore(int level);
    void exportScore(std::string best, int level);
    sf::Text getBestScore1() const {return bestScore1;};
    sf::Text getBestScore2() const {return bestScore2;};
    sf::Text getBestScore3() const {return bestScore3;};
};

#endif // SCORE_H_INCLUDED
