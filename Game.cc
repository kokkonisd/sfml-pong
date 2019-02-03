#include "Game.hh"

Game::Game (int width, int height, string title)
:
    sf::RenderWindow(sf::VideoMode(width, height), title),
    _leftPong(Pong(width / 40, height / 5, 0.1)),
    _rightPong(Pong(width / 40, height / 5, 0.1))
{
    _leftPong.setPosition(0, height / 2 - _leftPong.getSize().y / 2);
    _rightPong.setPosition(width - _rightPong.getSize().x, height / 2 - _rightPong.getSize().y / 2);
}


void Game::play ()
{
    while (isOpen()) {
        sf::Event event;

        while (pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    close();
                    break;

                case sf::Event::KeyPressed:
                    handleMoveKeyEvent(event.key.code, true);
                    break;

                case sf::Event::KeyReleased:
                    handleMoveKeyEvent(event.key.code, false);
                    break;

                default:
                    break;
            }
        }

        if (upFlagLeft) --_leftPong;
        if (downFlagLeft) ++_leftPong;
        if (upFlagRight) --_rightPong;
        if (downFlagRight) ++_rightPong;

        clear();
        draw(_leftPong);
        draw(_rightPong);
        display();
    }
}


void Game::handleMoveKeyEvent (int keyCode, bool isKeyPressed)
{
    if (keyCode == sf::Keyboard::W) upFlagLeft = isKeyPressed;
    if (keyCode == sf::Keyboard::S) downFlagLeft = isKeyPressed;
    if (keyCode == sf::Keyboard::Up) upFlagRight = isKeyPressed;
    if (keyCode == sf::Keyboard::Down) downFlagRight = isKeyPressed;
}
