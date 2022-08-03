#include <SFML/Graphics.hpp>
#include <iostream> // temp
#include <math.h> // pow
#include <cstdlib> // abs
#include <cstdlib> // rand
#include <ctime> // seed for srand
#include <string>
#include "textToDisplay.h"
#include "paddle.h"
#include "player.h"
#include "ball.h"

// GLOBALS
const int WINDOW_WIDTH = 1000, WINDOW_HEIGHT = 800;
sf::RenderWindow WINDOW(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "PONG GAME");
sf::Font FONT;
sf::Vertex MIDDLE_LINE[] =
{
    sf::Vertex(sf::Vector2f(WINDOW_WIDTH/2, 0)),
    sf::Vertex(sf::Vector2f(WINDOW_WIDTH/2, WINDOW_HEIGHT))
};
Player leftPlayer{Paddle(30, WINDOW_HEIGHT/2), TextToDisplay(WINDOW_WIDTH/4, 50)}, rightPlayer{Paddle(WINDOW_WIDTH-30, WINDOW_HEIGHT/2), TextToDisplay(WINDOW_WIDTH*3/4, 50)};
Ball ball;

//// FUNCTIONS
float getRandNum() { return ((double)std::rand()) / (RAND_MAX); }
float getRandNum(int minNum, int maxNum) { return getRandNum() * (maxNum - minNum + 1) + minNum ; }

void updateGame();

int main()
{
    sf::Vector2f temp(sf::Vector2f(5.5, 10.5) - sf::Vector2f(1.5, 5.5));
    std::cout << temp.x << ' ' << temp.y;
    std::srand(time(NULL)); // SET SEED FOR RNG

    // PREPARATION
    FONT.loadFromFile("./fonts/ComicSansMS.ttf");
    sf::Clock clock;

    while (WINDOW.isOpen())
    {

        // EVENT HANDLING
        sf::Event event;
        while (WINDOW.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                WINDOW.close();
        }

        // UPDATE
        if (clock.getElapsedTime().asMilliseconds() > 8) // around 120 times per second update game.
        {
            clock.restart();
            updateGame();
        }

    }

    return 0;
}
void updateGame()
{
    // KEYBOARD INPUT

    // LEFT PADDLE MOVEMENT
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        leftPlayer.paddle.move(UP);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        leftPlayer.paddle.move(DOWN);

    // RIGHT PADDLE MOVEMENT
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        rightPlayer.paddle.move(UP);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        rightPlayer.paddle.move(DOWN);

    // BALL UPDATE
    ball.update();


    // WINDOW UPDATE
    WINDOW.clear();
    WINDOW.draw(leftPlayer.paddle.shapeObject);
    WINDOW.draw(leftPlayer.pointsToDisplay.textObject);
    WINDOW.draw(rightPlayer.paddle.shapeObject);
    WINDOW.draw(rightPlayer.pointsToDisplay.textObject);
    WINDOW.draw(ball.shapeObject);
    WINDOW.draw(MIDDLE_LINE, 2, Lines);
    WINDOW.display();
}
