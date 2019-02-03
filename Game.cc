#include "Game.hh"

Game::Game (int width, int height, string title)
:
    sf::RenderWindow(sf::VideoMode(width, height), title),
    _leftPong(sf::RectangleShape(sf::Vector2f(width / 40, height / 5))),
    _rightPong(sf::RectangleShape(sf::Vector2f(width / 40, height / 5))),
    _pongHeight(height / 5),
    _pongWidth(width / 40)
{
    _leftPong.setPosition(0, height / 2 - _pongHeight / 2);
    _rightPong.setPosition(width - _pongWidth, height / 2 - _pongHeight / 2);
}

void Game::play ()
{
    while (isOpen()) {
        sf::Event event;

        while (pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                close();
        }

        clear();
        draw(_leftPong);
        draw(_rightPong);
        display();
    }
}
