#include "Game.hh"

Game::Game (int width, int height, string title)
:
    sf::RenderWindow(sf::VideoMode(width, height), title),
    _leftPaddle(Paddle(width / 40, height / 5, 0.1)),
    _rightPaddle(Paddle(width / 40, height / 5, 0.1))
{
    _leftPaddle.setPosition(0, height / 2 - _leftPaddle.getSize().y / 2);
    _rightPaddle.setPosition(width - _rightPaddle.getSize().x, height / 2 - _rightPaddle.getSize().y / 2);
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

        handlePaddleMovement();

        clear();
        draw(_leftPaddle);
        draw(_rightPaddle);
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


void Game::handlePaddleMovement ()
{
    if (upFlagLeft && _leftPaddle.getPosition().y > 0)
        --_leftPaddle;

    if (downFlagLeft && _leftPaddle.getPosition().y + _leftPaddle.getSize().y < getSize().y)
        ++_leftPaddle;

    if (upFlagRight && _rightPaddle.getPosition().y > 0)
        --_rightPaddle;

    if (downFlagRight && _rightPaddle.getPosition().y + _rightPaddle.getSize().y < getSize().y)
        ++_rightPaddle;
}
