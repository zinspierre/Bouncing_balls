#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <cmath>
#include <string>
#include <sstream>
#include "Game.h"
#include "Menu.h"
#include "Score.h"

std::string to_string(float value);


int main()
{
    while (true && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        float LEVEL(1);
        float SPEEDEASY(1800);
        float SPEEDMEDIUM(1100);
        float SPEEDHARD(800);
        int RECORDLEVEL(0);

        Game* game = new Game(20, 1);
        Menu* menu = new Menu();
        Score* score = new Score();

        sf::Font font4;
        font4.loadFromFile("arial.ttf");

        sf::Text text1;
        sf::Text text2;
        sf::Text text3;
        text1.setFont(font4);
        text2.setFont(font4);
        text3.setFont(font4);
        text1.setCharacterSize(50);
        text2.setCharacterSize(50);
        text3.setCharacterSize(50);
        text1.setStyle(sf::Text::Bold);
        text2.setStyle(sf::Text::Bold);
        text3.setStyle(sf::Text::Bold);
        text1.setString("1");
        text2.setString("2");
        text3.setString("3");
        text1.setColor(sf::Color(0, 100, 0));
        text2.setColor(sf::Color(0, 0, 100));
        text3.setColor(sf::Color(100, 0, 0));
        text1.setPosition(sf::Vector2f(111,32));
        text2.setPosition(sf::Vector2f(111,139));
        text3.setPosition(sf::Vector2f(111,246));
        while((menu->win).isOpen() && LEVEL == 1)
        {
            sf::Event event2;
            while (menu->win.pollEvent(event2))
            {
                if (event2.type == sf::Event::Closed) menu->win.close();
                switch(menu->choice())
                {
                    case 0 : break;
                    case 1 : LEVEL = SPEEDEASY;
                        RECORDLEVEL = 1;
                        break;
                    case 2 : LEVEL = SPEEDMEDIUM;
                        RECORDLEVEL = 2;
                        break;
                    case 3 : LEVEL = SPEEDHARD;
                        RECORDLEVEL = 3;
                        break;
                }
            }
            menu->win.draw(menu->getLevel1());
            menu->win.draw(menu->getLevel2());
            menu->win.draw(menu->getLevel3());
            menu->win.draw(text1);
            menu->win.draw(text2);
            menu->win.draw(text3);
            menu->win.display();
            menu->win.clear(sf::Color::Black);
        }
        score->importScore(RECORDLEVEL);


        // Font and Text
        //---------------------------------------------------------------------------
        sf::Font font;
        sf::Font font2;
        sf::Font font3;
        if (!font.loadFromFile("Escapei.ttf") || !font2.loadFromFile("arial.ttf")
            || !font3.loadFromFile("DigitaldreamFat.ttf"))
        {
            return 0;
        }
        sf::Text textTime;
        textTime.setFont(font);
        textTime.setCharacterSize(50);
        textTime.setColor(sf::Color(100,150,255,150));
        textTime.setStyle(sf::Text::Bold);
        textTime.setPosition(10,540);

        sf::Text endGame;
        endGame.setFont(font2);
        endGame.setCharacterSize(75);
        endGame.setColor(sf::Color::Red);
        endGame.setStyle(sf::Text::Bold);
        endGame.setPosition(180,225);
        endGame.setString("YOU LOSE !!!!");

        sf::Text textNumber;
        textNumber.setFont(font3);
        textNumber.setCharacterSize(45);
        textNumber.setColor(sf::Color(215, 48, 0));
        textNumber.setStyle(sf::Text::Bold);
        textNumber.setPosition(760,540);

        sf::Text newRecord;
        newRecord.setFont(font2);
        newRecord.setCharacterSize(50);
        newRecord.setColor(sf::Color::Yellow);
        newRecord.setStyle(sf::Text::Bold);
        newRecord.setPosition(180,475);
        newRecord.setString("NEW RECORD!!!");

        sf::Text level;
        level.setFont(font3);
        level.setCharacterSize(20);
        level.setColor(sf::Color(215, 48, 0));
        level.setStyle(sf::Text::Bold);
        level.setPosition(670,10);
        level.setString("LEVEL " + to_string(RECORDLEVEL));

        //--------------------------------------------------------------------------

        //Texture and sprite
        //--------------------------------------------------------------------------
        sf::Texture texture;
        texture.loadFromFile("fond.png", sf::IntRect(0,0,800,600));
        sf::Sprite sprite;
        sprite.setTexture(texture);
        //--------------------------------------------------------------------------


        srand (time(NULL));
        sf::Clock counter;
        sf::Clock time;
        sf::Clock fpsCounter;

        sf::SoundBuffer buffer;
        buffer.loadFromFile("sound.wav");
        sf::Sound sound;
        sound.setBuffer(buffer);

        sf::SoundBuffer buffer2;
        buffer2.loadFromFile("golf.wav");
        sf::Sound sound2;
        sound2.setBuffer(buffer2);


        sf::Music music;
        music.openFromFile("music.wav");
        music.play();
        music.setVolume(50);

        game->addBall();
        while ((game->app).isOpen() && (score->scoreWin).isOpen())
        {
            game->app.draw(sprite);
            game->limitation();
            //setString to Text
            //----------------------------------------------------------------------
            std::string temp = to_string(time.getElapsedTime().asSeconds());
            textTime.setString(temp);
            temp = to_string(game->getVectBalls().size());
            textNumber.setString(temp);
            //----------------------------------------------------------------------

            //add a new ball every 5 second
            //----------------------------------------------------------------------
            if (counter.getElapsedTime().asSeconds() >= 5)
            {
                game->addBall();
                counter.restart();
            }
            //----------------------------------------------------------------------

            //move balls
            //----------------------------------------------------------------------
            if (fpsCounter.getElapsedTime().asMicroseconds() > LEVEL )
            {
                if (game->move_balls() == 1) sound2.play();
                fpsCounter.restart();
            }
            //----------------------------------------------------------------------

            //Collision and end of game
            //----------------------------------------------------------------------
            if (game->collision_balls() == 1) sound2.play();
            if (game->collision() == 1)
                {
                    sound.play();
                    bool isNewRecord = false;
                    float scoreOld = score->importScore(RECORDLEVEL);
                    if (time.getElapsedTime().asSeconds() >= scoreOld)
                    {
                        score->exportScore(to_string(time.getElapsedTime().asSeconds()), RECORDLEVEL);
                        isNewRecord = true;
                    }

                    sf::Event event2;
                    while (!sf::Keyboard::isKeyPressed(sf::Keyboard::Return)
                           && !sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)
                           && !sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    {
                        if (isNewRecord) game->app.draw(newRecord);
                        game->app.draw(endGame);
                        game->app.draw(textTime);
                        game->app.draw(level);
                        game->app.display();
                        game->app.clear();
                        textTime.setPosition(250,350);
                        textTime.setCharacterSize(80);
                        textTime.setColor(sf::Color::Cyan);
                    }
                    game->app.close();
                    delete game;
                    delete menu;
                    delete score;
                    break;
                }
            //----------------------------------------------------------------------

            sf::Event event;
            while (game->app.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) game->app.close();
                game->mouse(game->app);
            }

            game->app.draw(game->getPlayer());
            game->app.draw(textTime);
            game->app.draw(textNumber);
            game->app.draw(level);
            game->draw_balls(game->app);

            game->app.display();
            game->app.clear();

            score->scoreWin.draw(score->getBestScore1());
            score->scoreWin.draw(score->getBestScore2());
            score->scoreWin.draw(score->getBestScore3());
            score->scoreWin.display();
            score->scoreWin.clear();
        }
    }
    return 0;
}

std::string to_string(float value)
{
    std::ostringstream os;
    os << value;
    return os.str();
}



