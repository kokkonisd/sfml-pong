#include "Game.hh"
#include <iostream>

Game::Game (int width, int height, string title)
:
    sf::RenderWindow(sf::VideoMode(width, height), title),
    _leftPaddle(Paddle(width / 40, height / 5, 0.1)),
    _rightPaddle(Paddle(width / 40, height / 5, 0.1)),
    _pong(Pong(width / 40, 0.02)),
    _upFlagLeft(false),
    _downFlagLeft(false),
    _upFlagRight(false),
    _downFlagRight(false),
    _leftPoints(0),
    _rightPoints(0)
{
    _leftPaddle.setPosition(0, height / 2 - _leftPaddle.getSize().y / 2);
    _rightPaddle.setPosition(width - _rightPaddle.getSize().x, height / 2 - _rightPaddle.getSize().y / 2);
}


void Game::play ()
{
    _pong.init(getSize().x, getSize().y);

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
        handlePongMovement();

        cout << _pong._speedX << endl;

        clear();
        draw(_leftPaddle);
        draw(_rightPaddle);
        draw(_pong);

        display();
    }
}


void Game::handleMoveKeyEvent (int keyCode, bool isKeyPressed)
{
    if (keyCode == sf::Keyboard::W) _upFlagLeft = isKeyPressed;
    if (keyCode == sf::Keyboard::S) _downFlagLeft = isKeyPressed;
    if (keyCode == sf::Keyboard::Up) _upFlagRight = isKeyPressed;
    if (keyCode == sf::Keyboard::Down) _downFlagRight = isKeyPressed;
}


void Game::handlePaddleMovement ()
{
    if (_upFlagLeft && _leftPaddle.getPosition().y > 0)
        --_leftPaddle;

    if (_downFlagLeft && _leftPaddle.getPosition().y + _leftPaddle.getSize().y < getSize().y)
        ++_leftPaddle;

    if (_upFlagRight && _rightPaddle.getPosition().y > 0)
        --_rightPaddle;

    if (_downFlagRight && _rightPaddle.getPosition().y + _rightPaddle.getSize().y < getSize().y)
        ++_rightPaddle;
}


void Game::handlePongMovement ()
{
    _pong.setPosition(_pong.getPosition().x + _pong._speedX * _pong._directionX,
                      _pong.getPosition().y + _pong._speedY * _pong._directionY);


    if (_pong.getPosition().y <= 0 || _pong.getPosition().y + _pong.getSize().y >= getSize().y) {
        _pong._directionY = - _pong._directionY;
    }

    if (_pong.getPosition().x <= _leftPaddle.getSize().x) {
        if (_pong.getPosition().y + _pong.getSize().y > _leftPaddle.getPosition().y &&
            _pong.getPosition().y < _leftPaddle.getPosition().y + _leftPaddle.getSize().y) {

            _pong._directionX = - _pong._directionX;
            _pong._speedX *= 1.5;
            _pong._speedY *= 1.2;

        } else {

            ++_rightPoints;
            _pong.init(getSize().x, getSize().y);

        }
    }

    if (_pong.getPosition().x + _pong.getSize().x >= getSize().x - _rightPaddle.getSize().x) {
        if (_pong.getPosition().y + _pong.getSize().y > _rightPaddle.getPosition().y &&
            _pong.getPosition().y < _rightPaddle.getPosition().y + _rightPaddle.getSize().y) {

            _pong._directionX = - _pong._directionX;
            _pong._speedX *= 1.5;
            _pong._speedY *= 1.2;

        } else {

            ++_leftPoints;
            _pong.init(getSize().x, getSize().y);

        }
    }
}
