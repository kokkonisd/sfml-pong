#include "Game.hh"
#include "Menu.hh"
#include <iostream>

using namespace std;


// Set Game constants
float Game::PADDLE_SPEED = 5.0;
// The Pong should start slower than the Paddles
float Game::PONG_BASE_SPEED = Game::PADDLE_SPEED / 5.0;
// We want the Pong to move faster horizontally than it does vertically
float Game::PONG_SPEED_MULTIPLIER_X = Game::PONG_BASE_SPEED * 0.8;
float Game::PONG_SPEED_MULTIPLIER_Y = Game::PONG_BASE_SPEED * 0.6;


Game::Game (int width, int height, string title)
:
    // Call to super() with the window dimensions & title
    sf::RenderWindow(sf::VideoMode(width, height), title),
    // Initialize the left and right Paddles 
    // Each one of them is 1/40th of the window's width wide and 1/5th of the
    // window's height tall
    _leftPaddle(Paddle(width / 40.0f, height / 5.0f, PADDLE_SPEED)),
    _rightPaddle(Paddle(width / 40.0f, height / 5.0f, PADDLE_SPEED)),
    // Initialize the pong, which is as wide as the Paddles
    _pong(Pong(width / 40, PONG_BASE_SPEED)),
    // Initialize the speed multipliers for the Pong
    _pongSpeedMultiplierX(PONG_SPEED_MULTIPLIER_X),
    _pongSpeedMultiplierY(PONG_SPEED_MULTIPLIER_Y),
    // Initialize the key flags for both Paddles
    _upFlagLeft(false),
    _downFlagLeft(false),
    _upFlagRight(false),
    _downFlagRight(false),
    // Initialize the point counters for both Paddles
    _leftPoints(0),
    _rightPoints(0)
{
    // Set a framerate limit in order to ensure that the game runs in the same
    // way on all machines
    setFramerateLimit(120);
    // Make the mouse invisible
    setMouseCursorVisible(false);

    // Center the Paddles vertically and align them in their horizontal 
    // positions
    _leftPaddle.setPosition(0, height / 2 - _leftPaddle.getSize().y / 2);
    _rightPaddle.setPosition(width - _rightPaddle.getSize().x,
                             height / 2 - _rightPaddle.getSize().y / 2);

    // Try to load the main font
    if (!_mainFont.loadFromFile("assets/fonts/MajorMonoDisplay-Regular.ttf")) {
        cout << "ERROR: Could not load font \"MajorMonoDisplay-Regular.ttf\"."\
                "Exiting." << endl;
        exit(1);
    }
}


void Game::play ()
{
    // Initialize the Pong's direction, speed and position
    _pong.init(getSize().x, getSize().y);
    // Initialize the point counters of both sides to 0
    _leftPoints = 0;
    _rightPoints = 0;
    // Reset the positions of the paddles
    _leftPaddle.setPosition(0, getSize().y / 2 - _leftPaddle.getSize().y / 2);
    _rightPaddle.setPosition(getSize().x - _rightPaddle.getSize().x,
                             getSize().y / 2 - _rightPaddle.getSize().y / 2);
    // Set up a boolean in order to start the game in "pause mode" (the players
    // will need to tap the Spacebar to start the game)
    bool gameStarted = false;

    // Start the main polling loop
    while (isOpen()) {
        sf::Event event;

        while (pollEvent(event)) {
            switch (event.type) {
                // Quit the game
                case sf::Event::Closed:
                    close();
                    break;

                case sf::Event::KeyPressed:
                    // Set the key flags based on the key code, stating that
                    // the key has just been pressed
                    handleMoveKeyEvent(event.key.code, true);

                    // If they pressed the Spacebar and the game hasn't started
                    // yet, start the game
                    if (event.key.code == sf::Keyboard::Space && !gameStarted)
                        gameStarted = true;

                    // If they press the Escape key, return to the main menu
                    if (event.key.code == sf::Keyboard::Escape)
                        mainMenu();

                    break;

                case sf::Event::KeyReleased:
                    // Set the key flags based on the key code, stating that
                    // the key has just been released
                    handleMoveKeyEvent(event.key.code, false);
                    break;

                default:
                    break;
            }
        }

        // Clear the screen
        clear();

        if (gameStarted) {
            // Handle the movement of both the Paddles and the Pong
            handlePaddleMovement();
            handlePongMovement();

            // Check the win condition (the game stops when one of the players
            // reaches a score of 11 points)
            if (_leftPoints == 11 || _rightPoints == 11)
                win(_leftPoints == 11 ?
                    "left player wins!" : "right player wins!");

        } else {
            // Keep the game in pause until the players press the Spacebar
            handlePreGameText();
        }

        // Draw the Paddles and the Pong
        draw(_leftPaddle);
        draw(_rightPaddle);
        draw(_pong);

        // Draw the score text
        handleScoreText();

        // Display the elements on the screen
        display();
    }
}


void Game::mainMenu ()
{
    Menu mainMenu("p0ng",
                  "",
                  { "play", "controls", "credits", "quit" },
                  {
                      [this]() { play(); },
                      [this]() { controlsMenu(); },
                      [this]() { creditsMenu(); },
                      [this]() { close(); }
                  },
                  _mainFont);

    mainMenu.show(*this);
}

void Game::controlsMenu ()
{
    Menu controlsMenu("controls",
                      L"left paddle:\n"\
                          "<w> to go up, <s> to go down\n"\
                          "\n"\
                          "right paddle:\n"\
                          "<↑> to go up, <↓> to go down",
                      { "back" },
                      { [this]() { mainMenu(); } },
                      _mainFont);

    controlsMenu.show(*this);
}

void Game::creditsMenu ()
{
    Menu creditsMenu("credits",
                     "made by dimitri kokkonis\n"\
                         "(kokkonisd.github.io)\n"\
                         "using c++ and sfml\n"\
                         "february 2019",
                     { "back" },
                     { [this]() { mainMenu(); } },
                     _mainFont);

    creditsMenu.show(*this);
}

void Game::win (string winMessage)
{
    Menu winScreen(winMessage,
                   to_string(_leftPoints) + " - " + to_string(_rightPoints),
                   { "play again", "main menu", "quit" },
                   {
                       [this]() { play(); },
                       [this]() { mainMenu(); },
                       [this]() { close(); }
                   },
                   _mainFont);

    winScreen.show(*this);
}


void Game::handleMoveKeyEvent (int keyCode, bool isKeyPressed)
{
    // Set the four movement flags (left up, left down, right up, right down)
    // to the boolean value passed in as an argument, in order to let the game
    // know when a Paddle should move based on if the player has pressed or
    // released the corresponding key
    if (keyCode == sf::Keyboard::W) _upFlagLeft = isKeyPressed;
    if (keyCode == sf::Keyboard::S) _downFlagLeft = isKeyPressed;
    if (keyCode == sf::Keyboard::Up) _upFlagRight = isKeyPressed;
    if (keyCode == sf::Keyboard::Down) _downFlagRight = isKeyPressed;
}


void Game::handlePaddleMovement ()
{
    // Move the left Paddle up if its movement flag is set and if it doesn't go
    // off-screen
    if (_upFlagLeft && _leftPaddle.getPosition().y > 0)
        --_leftPaddle;

    // Move the left Paddle down if its movement flag is set and if it doesn't
    // go off-screen
    if (_downFlagLeft &&
            _leftPaddle.getPosition().y + _leftPaddle.getSize().y
            < getSize().y)
        ++_leftPaddle;

    // Move the right Paddle up if its movement flag is set and if it doesn't
    // go off-screen
    if (_upFlagRight && _rightPaddle.getPosition().y > 0)
        --_rightPaddle;

    // Move the right Paddle down if its movement flag is set and if it doesn't
    // go off-screen
    if (_downFlagRight &&
            _rightPaddle.getPosition().y + _rightPaddle.getSize().y
            < getSize().y)
        ++_rightPaddle;
}


void Game::handlePongMovement ()
{
    // Update the Pong's position based on its speed and direction on both axes
    _pong.setPosition(_pong.getPosition().x +
                          _pong.getSpeedX() * _pong.getDirectionX(),
                      _pong.getPosition().y +
                          _pong.getSpeedY() * _pong.getDirectionY());


    // If the Pong touches the top or the bottom of the screen, flip its
    // direction on the Y axis
    if (_pong.getPosition().y <= 0 ||
            _pong.getPosition().y + _pong.getSize().y >= getSize().y)
        _pong.flipDirectionY();

    // If the Pong hits the left side of the screen
    if (_pong.getPosition().x <= _leftPaddle.getSize().x) {
        // If the Pong is contained within the left Paddle vertically
        if ((_pong.getPosition().y + _pong.getSize().y
                > _leftPaddle.getPosition().y)
                &&
                (_pong.getPosition().y
                < _leftPaddle.getPosition().y + _leftPaddle.getSize().y)) {

            // Flip the Pong's horizontal direction
            _pong.flipDirectionX();
            // Increase the Pong's speed on both axes
            _pong.setSpeedX(_pong.getSpeedX() + _pongSpeedMultiplierX);
            _pong.setSpeedY(_pong.getSpeedY() + _pongSpeedMultiplierY);

        // If the Pong doesn't hit the left Paddle
        } else {
            // Increase the right Paddle's point count
            ++_rightPoints;
            // Reset the Pong
            _pong.init(getSize().x, getSize().y);
        }
    }

    // If the Pong hits the right side of the screen
    if (_pong.getPosition().x + _pong.getSize().x
            >= getSize().x - _rightPaddle.getSize().x) {
        // If the Pong is contained within the right Paddle vertically
        if ((_pong.getPosition().y + _pong.getSize().y
                > _rightPaddle.getPosition().y)
                &&
                (_pong.getPosition().y <
                _rightPaddle.getPosition().y + _rightPaddle.getSize().y)) {

            // Flip the Pong's horizontal direction
            _pong.flipDirectionX();
            // Increase the Pong's speed on both axes
            _pong.setSpeedX(_pong.getSpeedX() + _pongSpeedMultiplierX);
            _pong.setSpeedY(_pong.getSpeedY() + _pongSpeedMultiplierY);

        // If the Pong doesn't hit the right Paddle
        } else {
            // Increase the left Paddle's point count
            ++_leftPoints;
            // Reset the Pong
            _pong.init(getSize().x, getSize().y);
        }
    }
}


void Game::handleScoreText ()
{
    // Stringstream to build the score string
    stringstream scoreText;
    // The text object to display the score string
    sf::Text score;

    // The score is formatted as "X - Y"
    scoreText << _leftPoints << " - " << _rightPoints;
    // Set the font for the score text
    score.setFont(_mainFont);
    // Set the score string as the text
    score.setString(scoreText.str());
    // Set the font size to 40
    score.setCharacterSize(40);
    // Center the score text horizontally and place it near the top of the
    // screen
    score.setPosition(getSize().x / 2.0f -
                          score.getLocalBounds().width / 2.0f - 5,
                      10);

    // Draw the score text
    draw(score);
}


void Game::handlePreGameText ()
{
    // Text object to hold the pre-game text
    sf::Text preGameText;
    // Set the font for the text object
    preGameText.setFont(_mainFont);
    // Set the text to notify players they need to press the Spacebar to start
    // the game
    preGameText.setString("press <space> to start");
    // Set font size to 20
    preGameText.setCharacterSize(20);
    // Center the pre-game text
    preGameText.setPosition(getSize().x / 2.0f -
                                preGameText.getLocalBounds().width / 2.0f - 5,
                            _pong.getPosition().y - 40);

    // Draw the pre-game text
    draw(preGameText);
}
