#include "Game.h"
#include <iostream>
#include <cmath>
#include <ctime>

Game::Game(int rad, int speed) :  radius(rad), app(sf::VideoMode(800, 600), "Balls", sf::Style::Default), initialSpeed(speed)
{
    app.setPosition(sf::Vector2i(317,80));
    app.setMouseCursorVisible(false);
    player.setRadius(17);
    player.setPosition(400,300);
    player.setFillColor(sf::Color(50,50,200,255));
    player.setOutlineColor(sf::Color::Black);
    player.setOutlineThickness(3);
}

void Game::limitation()
{
    if (player.getPosition().x < 0) player.setPosition(sf::Vector2f(0, player.getPosition().y));
    if (player.getPosition().y < 0) player.setPosition(sf::Vector2f(player.getPosition().x, 0));
    if (player.getPosition().x > 805 - radius * 2) player.setPosition(sf::Vector2f(805 - radius * 2, player.getPosition().y));
    if (player.getPosition().y > 605 - radius * 2) player.setPosition(sf::Vector2f(player.getPosition().x, 605 - 2 * radius));
}

void Game::addBall()
{
    int position_x = (rand() % 700)+21;
    int position_y = (rand() % 250)+21;
    if ((std::abs(position_x - player.getPosition().x)) < 50 &&
        std::abs(position_y - player.getPosition().y) < 50)
        {
            position_x = 21;
            position_y = 21;
        }
    sf::CircleShape ball;
    ball.setPosition(position_x, position_y);
    ball.setRadius(radius);
    ball.setFillColor(sf::Color(255,254,255));
    ball.setOutlineColor(sf::Color::Black);
    ball.setOutlineThickness(1);

    std::vector<int> tempVectX;
    std::vector<int> tempVectY;
    tempVectX.push_back(position_x);
    tempVectY.push_back(position_y);
    vectBalls.push_back(ball);
    vectX.push_back(tempVectX);
    vectY.push_back(tempVectY);
    int rand1 = (rand() % 2)+1;
    int rand2 = (rand() % 2)+1;
    std::cout << rand1 << rand2 << std::endl;
    if (rand1 == 1) vectSpeedX.push_back(initialSpeed);
    else vectSpeedX.push_back(-initialSpeed);
    if (rand2 == 1) vectSpeedY.push_back(initialSpeed);
    else vectSpeedY.push_back(-initialSpeed);
}

void Game::draw_balls(sf::RenderWindow& app)
{
    for (unsigned int i = 0; i < vectBalls.size(); ++i)
    {
        app.draw(vectBalls.at(i));
    }
}

int Game::move_balls()
{
    int return_value(0);
    for (unsigned int i = 0; i < vectBalls.size(); ++i)
    {
        {
            if (vectBalls.at(i).getPosition().x == 780 || vectBalls.at(i).getPosition().x == 0)
            {
                vectSpeedX.at(i) = -vectSpeedX.at(i);
                return_value = 1;
            }
            else if (vectBalls.at(i).getPosition().y == 570 || vectBalls.at(i).getPosition().y == -5)
            {
                vectSpeedY.at(i) = -vectSpeedY.at(i);
                return_value = 1;
            }
        }
        vectBalls.at(i).move(vectSpeedX.at(i), vectSpeedY.at(i));
        vectX.at(i).push_back(vectBalls.at(i).getPosition().x);
        vectY.at(i).push_back(vectBalls.at(i).getPosition().y);
    }
    return return_value;
}


int Game::collision()
{
    for (unsigned int i = 0; i < vectBalls.size(); ++i)
    {
        if ((std::abs(player.getPosition().x - vectBalls.at(i).getPosition().x) < 35)
            && (std::abs(player.getPosition().y - vectBalls.at(i).getPosition().y) < 35))
        {
            std::cout << "YOU LOSE IN " << time.getElapsedTime().asSeconds() << " S." << std::endl;
            return 1;
        }
    }
    return 0;
}


void Game::mouse(sf::RenderWindow& app)
{
    sf::Vector2i position;
    position = sf::Mouse::getPosition(app);
    player.setPosition(position.x, position.y);
}

int Game::collision_balls()
{
    int return_value(0);
    for (unsigned int i = 0; i < vectBalls.size(); ++i)
    {
        for (unsigned int j = 0; j < vectBalls.size(); ++j)
        {
            if (!(vectBalls.at(i).getPosition().x == vectBalls.at(j).getPosition().x
                  && vectBalls.at(i).getPosition().y == vectBalls.at(j).getPosition().y))
            {
                if ((std::abs(vectBalls.at(i).getPosition().x - vectBalls.at(j).getPosition().x) < 25)
                    &&(std::abs(vectBalls.at(i).getPosition().y - vectBalls.at(j).getPosition().y) < 25))
                {
                    if (vectSpeedX.at(i) * vectSpeedX.at(j) > 0)
                    {
                        vectSpeedX.at(i) =  -vectSpeedX.at(i);
                        vectSpeedY.at(j) =  -vectSpeedY.at(j);
                    }
                    if (vectSpeedX.at(i) * vectSpeedX.at(j) < 0)
                    {
                        vectSpeedX.at(i) =  vectSpeedX.at(i);
                        vectSpeedY.at(i) =  -vectSpeedY.at(i);
                        vectSpeedX.at(j) =  -vectSpeedX.at(j);
                        vectSpeedY.at(j) =  -vectSpeedY.at(j);
                    }
                    vectBalls.at(i).move(vectSpeedX.at(i), vectSpeedY.at(i));
                    vectBalls.at(j).move(vectSpeedX.at(j), vectSpeedY.at(j));
                    return_value = 1;
                }
            }
        }
    }
    return return_value;
}


