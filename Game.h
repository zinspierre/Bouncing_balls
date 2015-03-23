#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <vector>



class Game
{
private:
    int radius;
    int initialSpeed;
    std::vector<std::vector<int> > vectX;
    std::vector<std::vector<int> > vectY;
    std::vector<sf::CircleShape> vectBalls;
    std::vector<int> vectSpeedX;
    std::vector<int> vectSpeedY;
    sf::CircleShape player;

public:
    sf::RenderWindow app;
    sf::Clock time;
    Game(int rad, int initialSpeed);
    virtual~Game(){};

    void limitation();
    int move_balls();
    void addBall();
    int collision();
    void mouse(sf::RenderWindow& app);
    void draw_balls(sf::RenderWindow& app);
    int collision_balls();

    std::vector<std::vector<int> > getVectX() const {return vectX;};
    std::vector<std::vector<int> > getVectY() const {return vectY;};
    std::vector<sf::CircleShape> getVectBalls() const {return vectBalls;};
    void setRadius(int rad) {radius = rad;};
    sf::CircleShape getPlayer() const {return player;};

};
#endif // GAME_H_INCLUDED
