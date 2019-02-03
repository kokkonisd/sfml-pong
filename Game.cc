#include "Game.hh"

Game::Game (int width, int height, string title)
:
    sf::RenderWindow(sf::VideoMode(width, height), title),
    _leftPong(Pong(width / 40, height / 5)),
    _rightPong(Pong(width / 40, height / 5))
{
    _leftPong.setPosition(0, height / 2 - _leftPong.getSize().y / 2);
    _rightPong.setPosition(width - _rightPong.getSize().x, height / 2 - _rightPong.getSize().y / 2);
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
