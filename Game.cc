#include "Game.hh"
#include <iostream>

using namespace std;

float Game::PADDLE_SPEED = 5.0;
float Game::PONG_BASE_SPEED = Game::PADDLE_SPEED / 5.0;
float Game::PONG_SPEED_MULTIPLIER_X = Game::PONG_BASE_SPEED * 0.8;
float Game::PONG_SPEED_MULTIPLIER_Y = Game::PONG_BASE_SPEED * 0.6;

Game::Game (int width, int height, string title)
:
    sf::RenderWindow(sf::VideoMode(width, height), title),
    _leftPaddle(Paddle(width / 40.0f, height / 5.0f, PADDLE_SPEED)),
    _rightPaddle(Paddle(width / 40.0f, height / 5.0f, PADDLE_SPEED)),
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
    setMouseCursorVisible(false);

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
    bool gameStarted = false;

    while (isOpen()) {
        sf::Event event;

        while (pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    close();
                    break;

                case sf::Event::KeyPressed:
                    handleMoveKeyEvent(event.key.code, true);

                    if (event.key.code == sf::Keyboard::Space && !gameStarted)
                        gameStarted = true;

                    if (event.key.code == sf::Keyboard::Escape) {
                        _leftPoints = 0;
                        _rightPoints = 0;
                        menu();
                    }

                    break;

                case sf::Event::KeyReleased:
                    handleMoveKeyEvent(event.key.code, false);
                    break;

                default:
                    break;
            }
        }

        clear();

        if (gameStarted) {
            handlePaddleMovement();
            handlePongMovement();
        } else {
            handlePreGameText();
        }

        draw(_leftPaddle);
        draw(_rightPaddle);
        draw(_pong);

        handleScoreText();

        display();
    }
}


void Game::menu ()
{
    Pong menuPong(20, 0);
    menuPong.setPosition(getSize().x / 2 - 80, getSize().y / 2 - 85);

    int selectedMenuItem = 0;
    int currentMenuState = 0;

    while (isOpen()) {
        sf::Event event;

        while (pollEvent(event)) {
            switch (event.type) {
                case sf::Event::Closed:
                    close();
                    break;

                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        case sf::Keyboard::Up:
                            if (selectedMenuItem > 0) {
                                selectedMenuItem--;
                                menuPong.setPosition(menuPong.getPosition().x, menuPong.getPosition().y - 100);
                            }

                            break;

                        case sf::Keyboard::Down:
                            if (selectedMenuItem < 3) {
                                selectedMenuItem++;
                                menuPong.setPosition(menuPong.getPosition().x, menuPong.getPosition().y + 100);
                            }

                            break;

                        case sf::Keyboard::Return:
                            if (currentMenuState == 0) {
                                if (selectedMenuItem == 0) play();
                                else if (selectedMenuItem == 1) currentMenuState = 1; // controls
                                else if (selectedMenuItem == 2) currentMenuState = 2; // credits
                                else close();
                            } else {
                                currentMenuState = 0;
                                selectedMenuItem = 0;
                                menuPong.setPosition(getSize().x / 2 - 80, getSize().y / 2 - 85);
                            }

                            break;

                        default:
                            break;
                    }

                default:
                    break;
            }
        }

        clear();

        switch (currentMenuState) {
            case 0:
                drawMenuItems();
                draw(menuPong);
                break;

            case 1:
                drawControlsItems();
                menuPong.setPosition(getSize().x / 2 - 80, getSize().y - 100);
                draw(menuPong);
                break;

            case 2:
                drawCreditsItems();
                menuPong.setPosition(getSize().x / 2 - 80, getSize().y - 100);
                draw(menuPong);
                break;

            default:
                break;
        }



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
            _pong.setSpeedX(_pong.getSpeedX() + _pongSpeedMultiplierX);
            _pong.setSpeedY(_pong.getSpeedY() + _pongSpeedMultiplierY);

        } else {

            ++_rightPoints;
            _pong.init(getSize().x, getSize().y);

        }
    }

    if (_pong.getPosition().x + _pong.getSize().x >= getSize().x - _rightPaddle.getSize().x) {
        if (_pong.getPosition().y + _pong.getSize().y > _rightPaddle.getPosition().y &&
            _pong.getPosition().y < _rightPaddle.getPosition().y + _rightPaddle.getSize().y) {

            _pong.flipDirectionX();
            _pong.setSpeedX(_pong.getSpeedX() + _pongSpeedMultiplierX);
            _pong.setSpeedY(_pong.getSpeedY() + _pongSpeedMultiplierY);

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


void Game::handlePreGameText ()
{
    sf::Text preGameText;
    preGameText.setFont(_mainFont);
    preGameText.setString("press <space> to start");
    preGameText.setCharacterSize(20);
    preGameText.setPosition(getSize().x / 2.0f - preGameText.getLocalBounds().width / 2.0f - 5,
                            _pong.getPosition().y - 40);

    draw(preGameText);
}


void Game::drawMenuItems ()
{
    sf::Text menuTitle;
    sf::Text menuPlayText;
    sf::Text menuControlsText;
    sf::Text menuCreditsText;
    sf::Text menuQuitText;

    menuTitle.setFont(_mainFont);
    menuTitle.setString("p0ng");
    menuTitle.setCharacterSize(70);
    menuTitle.setPosition(getSize().x / 2.0f - menuTitle.getLocalBounds().width / 2.0f - 5, 10);

    menuPlayText.setFont(_mainFont);
    menuPlayText.setString("play");
    menuPlayText.setCharacterSize(40);
    menuPlayText.setPosition(getSize().x / 2.0f - 10, getSize().y / 2.0f - 100);

    menuControlsText.setFont(_mainFont);
    menuControlsText.setString("controls");
    menuControlsText.setCharacterSize(40);
    menuControlsText.setPosition(getSize().x / 2.0f - 10, getSize().y / 2.0f);

    menuCreditsText.setFont(_mainFont);
    menuCreditsText.setString("credits");
    menuCreditsText.setCharacterSize(40);
    menuCreditsText.setPosition(getSize().x / 2.0f - 10, getSize().y / 2.0f + 100);

    menuQuitText.setFont(_mainFont);
    menuQuitText.setString("quit");
    menuQuitText.setCharacterSize(40);
    menuQuitText.setPosition(getSize().x / 2.0f - 10, getSize().y / 2.0f + 200);

    draw(menuTitle);
    draw(menuPlayText);
    draw(menuControlsText);
    draw(menuCreditsText);
    draw(menuQuitText);
}


void Game::drawControlsItems ()
{
    sf::Text menuTitle;
    sf::Text menuText;
    sf::Text backText;

    menuTitle.setFont(_mainFont);
    menuTitle.setString("controls");
    menuTitle.setCharacterSize(70);
    menuTitle.setPosition(getSize().x / 2.0f - menuTitle.getLocalBounds().width / 2.0f - 5, 10);

    menuText.setFont(_mainFont);
    menuText.setString(L"left paddle:\n<w> to go up, <s> to go down\n\nright paddle:\n<↑> to go up, <↓> to go down");
    menuText.setCharacterSize(30);
    menuText.setPosition(getSize().x / 2.0f - menuText.getLocalBounds().width / 2.0f - 5,
                         getSize().y / 2.0f - 100);

    backText.setFont(_mainFont);
    backText.setString("back");
    backText.setCharacterSize(40);
    backText.setPosition(getSize().x / 2.0f - 15, getSize().y - 116);

    draw(menuTitle);
    draw(menuText);
    draw(backText);
}


void Game::drawCreditsItems ()
{
    sf::Text menuTitle;
    sf::Text menuText;
    sf::Text backText;

    menuTitle.setFont(_mainFont);
    menuTitle.setString("credits");
    menuTitle.setCharacterSize(70);
    menuTitle.setPosition(getSize().x / 2.0f - menuTitle.getLocalBounds().width / 2.0f - 5, 10);

    menuText.setFont(_mainFont);
    menuText.setString("made by dimitris kokkonis\n(kokkonisd.github.io)\nusing c++ and sfml\nfebruary 2019");
    menuText.setCharacterSize(35);
    menuText.setPosition(getSize().x / 2.0f - menuText.getLocalBounds().width / 2.0f - 5,
                         getSize().y / 2.0f - 100);

    backText.setFont(_mainFont);
    backText.setString("back");
    backText.setCharacterSize(40);
    backText.setPosition(getSize().x / 2.0f - 15, getSize().y - 116);

    draw(menuTitle);
    draw(menuText);
    draw(backText);
}
