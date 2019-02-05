#include "Game.hh"
#include <iostream>

using namespace std;

float Game::PADDLE_SPEED = 5.0;
float Game::PONG_BASE_SPEED = Game::PADDLE_SPEED / 6.0;
float Game::PONG_SPEED_MULTIPLIER_X = 1.4;
float Game::PONG_SPEED_MULTIPLIER_Y = 1.2;

Game::Game (int width, int height, string title)
:
    sf::RenderWindow(sf::VideoMode(width, height), title),
    _leftPaddle(Paddle(width / 40, height / 5, PADDLE_SPEED)),
    _rightPaddle(Paddle(width / 40, height / 5, PADDLE_SPEED)),
    _pong(Pong(width / 40, PONG_BASE_SPEED)),
    _pongSpeedMultiplierX(PONG_SPEED_MULTIPLIER_X),
    _pongSpeedMultiplierY(PONG_SPEED_MULTIPLIER_Y),
    _upFlagLeft(false),
    _downFlagLeft(false),
    _upFlagRight(false),
    _downFlagRight(false),
    _leftPoints(0),
    _rightPoints(0)
{
    setFramerateLimit(120);

    _leftPaddle.setPosition(0, height / 2 - _leftPaddle.getSize().y / 2);
    _rightPaddle.setPosition(width - _rightPaddle.getSize().x, height / 2 - _rightPaddle.getSize().y / 2);

    if (!_mainFont.loadFromFile("assets/fonts/MajorMonoDisplay-Regular.ttf")) {
        cout << "ERROR: Could not load font \"MajorMonoDisplay-Regular.ttf\". Exiting." << endl;
        exit(1);
    }
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

        clear();

        draw(_leftPaddle);
        draw(_rightPaddle);
        draw(_pong);

        handleScoreText();

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
    _pong.setPosition(_pong.getPosition().x + _pong.getSpeedX() * _pong.getDirectionX(),
                      _pong.getPosition().y + _pong.getSpeedY() * _pong.getDirectionY());


    if (_pong.getPosition().y <= 0 || _pong.getPosition().y + _pong.getSize().y >= getSize().y) {
        _pong.flipDirectionY();
    }

    if (_pong.getPosition().x <= _leftPaddle.getSize().x) {
        if (_pong.getPosition().y + _pong.getSize().y > _leftPaddle.getPosition().y &&
            _pong.getPosition().y < _leftPaddle.getPosition().y + _leftPaddle.getSize().y) {

            _pong.flipDirectionX();
            _pong.setSpeedX(_pong.getSpeedX() * _pongSpeedMultiplierX);
            _pong.setSpeedY(_pong.getSpeedY() * _pongSpeedMultiplierY);

        } else {

            ++_rightPoints;
            _pong.init(getSize().x, getSize().y);

        }
    }

    if (_pong.getPosition().x + _pong.getSize().x >= getSize().x - _rightPaddle.getSize().x) {
        if (_pong.getPosition().y + _pong.getSize().y > _rightPaddle.getPosition().y &&
            _pong.getPosition().y < _rightPaddle.getPosition().y + _rightPaddle.getSize().y) {

            _pong.flipDirectionX();
            _pong.setSpeedX(_pong.getSpeedX() * _pongSpeedMultiplierX);
            _pong.setSpeedY(_pong.getSpeedY() * _pongSpeedMultiplierY);

        } else {

            ++_leftPoints;
            _pong.init(getSize().x, getSize().y);

        }
    }
}


void Game::handleScoreText ()
{
    stringstream scoreText;
    sf::Text score;

    scoreText << _leftPoints << " - " << _rightPoints;
    score.setFont(_mainFont);
    score.setString(scoreText.str());
    score.setCharacterSize(40);
    score.setPosition(getSize().x / 2.0f - score.getLocalBounds().width / 2.0f - 5, 10);

    draw(score);
}
