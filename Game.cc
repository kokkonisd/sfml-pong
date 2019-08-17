#include "Game.hh"
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
                        menu();

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


void Game::menu ()
{
    // Draw a Pong that will be used as a "cursor" to indicate the user's 
    // current choice on the menu
    Pong menuPong(20, 0);
    // Set the position of the Pong cursor to align it with the first element
    menuPong.setPosition(getSize().x / 2 - 80, getSize().y / 2 - 85);

    // Set two variables to control both the selected item and the current
    // state of the menu screen
    int selectedMenuItem = 0;
    int currentMenuState = 0;

    // Set up a polling loop
    while (isOpen()) {
        sf::Event event;

        while (pollEvent(event)) {
            switch (event.type) {
                // Close the window
                case sf::Event::Closed:
                    close();
                    break;

                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        // When the up arrow key is pressed, move the Pong
                        // cursor up and decrease the selectedMenuItem counter
                        case sf::Keyboard::Up:
                            if (selectedMenuItem > 0) {
                                selectedMenuItem--;
                                menuPong.setPosition(menuPong.getPosition().x,
                                                     menuPong.getPosition().y
                                                        - 100);
                            }

                            break;

                        // When the down arrow key is pressed, move the Pong
                        // cursor down and increase the selectedMenuItem
                        // counter
                        case sf::Keyboard::Down:
                            if (selectedMenuItem < 3) {
                                selectedMenuItem++;
                                menuPong.setPosition(menuPong.getPosition().x,
                                                     menuPong.getPosition().y
                                                        + 100);
                            }

                            break;

                        // When the Enter (or Return) key is pressed, set the
                        // current menu state based on the currently selected
                        // menu item
                        case sf::Keyboard::Return:
                            // If we're in the Main Menu
                            if (currentMenuState == 0) {
                                // If it's the first choice, launch the game
                                if (selectedMenuItem == 0)
                                    play();
                                // If it's the second choice, show the Controls
                                // screen
                                else if (selectedMenuItem == 1)
                                    currentMenuState = 1;
                                // If it's the third choice, show the Credits
                                // screen
                                else if (selectedMenuItem == 2)
                                    currentMenuState = 2;
                                // If it's the fourth choice, quit the game
                                else
                                    close();
                            // If we're in one of the other two screens
                            // (Controls or Credits) then it means that the
                            // player has pushed the `back` button, so we need
                            // to go back to the main menu
                            } else {
                                // Reset the counters and the Pong cursor for
                                // the main menu
                                currentMenuState = 0;
                                selectedMenuItem = 0;
                                menuPong.setPosition(getSize().x / 2 - 80,
                                                     getSize().y / 2 - 85);
                            }

                            break;

                        default:
                            break;
                    }

                default:
                    break;
            }
        }

        // Clear the screen
        clear();

        // The FSM controlling what is drawn based on the current state of the
        // menu
        switch (currentMenuState) {
            // Main menu state
            case 0:
                drawMenuItems();
                draw(menuPong);
                break;

            // Controls screen state
            case 1:
                drawControlsItems();
                menuPong.setPosition(getSize().x / 2 - 80, getSize().y - 100);
                draw(menuPong);
                break;

            // Credits screen state
            case 2:
                drawCreditsItems();
                menuPong.setPosition(getSize().x / 2 - 80, getSize().y - 100);
                draw(menuPong);
                break;

            default:
                break;
        }

        // Display the screen
        display();
    }
}


void Game::win (string winMessage)
{
    // Pong cursor to control the menu of the win screen
    Pong winPong(20, 0);
    // Set the position of the Pong cursor so that it is aligned next to the
    // first menu element
    winPong.setPosition(getSize().x / 2 - 80, getSize().y / 2 - 85 + 100);

    // Counter to handle the currently selected menu item from the win screen
    int selectedWinItem = 0;

    // Polling loop
    while (isOpen()) {
        sf::Event event;

        while (pollEvent(event)) {
            switch (event.type) {
                // Quit the game
                case sf::Event::Closed:
                    close();
                    break;

                case sf::Event::KeyPressed:
                    switch (event.key.code) {
                        // If the up arrow key is pressed, decrease the 
                        // selected item counter and move the Pong cursor up
                        case sf::Keyboard::Up:
                            if (selectedWinItem > 0) {
                                selectedWinItem--;
                                winPong.setPosition(winPong.getPosition().x,
                                                    winPong.getPosition().y
                                                        - 100);
                            }

                            break;

                        // If the down arrow key is pressed, increase the 
                        // selected item counter and move the Pong cursor down
                        case sf::Keyboard::Down:
                            if (selectedWinItem < 2) {
                                selectedWinItem++;
                                winPong.setPosition(winPong.getPosition().x,
                                                    winPong.getPosition().y
                                                        + 100);
                            }

                            break;

                        // If the Enter (or Return) key is pressed, perform an
                        // action based on the currently selected menu item
                        case sf::Keyboard::Return:
                            // If the first one is selected, launch another
                            // game of Pong
                            if (selectedWinItem == 0) play();
                            // If the second one is selected, go back to the
                            // main menu
                            else if (selectedWinItem == 1) menu();
                            // If the third one is selected, quit the game
                            else close();

                            break;

                        default:
                            break;
                    }

                default:
                    break;
            }
        }

        // Clear the screen
        clear();

        // Draw the score text
        handleScoreText();

        // Draw the win text and win screen menu items
        drawWinItems(winMessage);

        // Draw the Pong cursor
        draw(winPong);

        // Display the elements on the screen
        display();
    }
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


void Game::drawMenuItems ()
{
    // Text objects for the menu title, the Play option, the Controls option,
    // the Credits option and the Quit option
    sf::Text menuTitle;
    sf::Text menuPlayText;
    sf::Text menuControlsText;
    sf::Text menuCreditsText;
    sf::Text menuQuitText;

    // Set up the title of the game
    menuTitle.setFont(_mainFont);
    menuTitle.setString("p0ng");
    menuTitle.setCharacterSize(70);
    menuTitle.setPosition(getSize().x / 2.0f -
                              menuTitle.getLocalBounds().width / 2.0f - 5,
                          10);

    // Set up the Play option
    menuPlayText.setFont(_mainFont);
    menuPlayText.setString("play");
    menuPlayText.setCharacterSize(40);
    menuPlayText.setPosition(getSize().x / 2.0f - 10,
                             getSize().y / 2.0f - 100);

    // Set up the Controls option
    menuControlsText.setFont(_mainFont);
    menuControlsText.setString("controls");
    menuControlsText.setCharacterSize(40);
    menuControlsText.setPosition(getSize().x / 2.0f - 10, getSize().y / 2.0f);

    // Set up the Credits option
    menuCreditsText.setFont(_mainFont);
    menuCreditsText.setString("credits");
    menuCreditsText.setCharacterSize(40);
    menuCreditsText.setPosition(getSize().x / 2.0f - 10,
                                getSize().y / 2.0f + 100);

    // Set up the Quit option
    menuQuitText.setFont(_mainFont);
    menuQuitText.setString("quit");
    menuQuitText.setCharacterSize(40);
    menuQuitText.setPosition(getSize().x / 2.0f - 10,
                             getSize().y / 2.0f + 200);

    // Draw the title and the options on the screen
    draw(menuTitle);
    draw(menuPlayText);
    draw(menuControlsText);
    draw(menuCreditsText);
    draw(menuQuitText);
}


void Game::drawControlsItems ()
{
    // Text objects for the Controls menu title, the menu text and the Back
    // option
    sf::Text menuTitle;
    sf::Text menuText;
    sf::Text backText;

    // Set up the menu title
    menuTitle.setFont(_mainFont);
    menuTitle.setString("controls");
    menuTitle.setCharacterSize(70);
    menuTitle.setPosition(getSize().x / 2.0f -
                              menuTitle.getLocalBounds().width / 2.0f - 5,
                          10);

    // Set up the menu text
    menuText.setFont(_mainFont);
    menuText.setString(L"left paddle:\n"\
                        "<w> to go up, <s> to go down\n\n"\
                        "right paddle:\n"\
                        "<↑> to go up, <↓> to go down");
    menuText.setCharacterSize(30);
    menuText.setPosition(getSize().x / 2.0f -
                             menuText.getLocalBounds().width / 2.0f - 5,
                         getSize().y / 2.0f - 100);

    // Set up the Back option
    backText.setFont(_mainFont);
    backText.setString("back");
    backText.setCharacterSize(40);
    backText.setPosition(getSize().x / 2.0f - 15, getSize().y - 116);

    // Draw the three text objects
    draw(menuTitle);
    draw(menuText);
    draw(backText);
}


void Game::drawCreditsItems ()
{
    // Text objects for the Credits menu title, the menu text and the Back
    // option
    sf::Text menuTitle;
    sf::Text menuText;
    sf::Text backText;

    // Set up the menu title
    menuTitle.setFont(_mainFont);
    menuTitle.setString("credits");
    menuTitle.setCharacterSize(70);
    menuTitle.setPosition(getSize().x / 2.0f - menuTitle.getLocalBounds().width / 2.0f - 5, 10);

    // Set up the menu text
    menuText.setFont(_mainFont);
    menuText.setString("made by dimitris kokkonis\n(kokkonisd.github.io)\nusing c++ and sfml\nfebruary 2019");
    menuText.setCharacterSize(35);
    menuText.setPosition(getSize().x / 2.0f - menuText.getLocalBounds().width / 2.0f - 5,
                         getSize().y / 2.0f - 100);

    // Set up the Back option
    backText.setFont(_mainFont);
    backText.setString("back");
    backText.setCharacterSize(40);
    backText.setPosition(getSize().x / 2.0f - 15, getSize().y - 116);

    // Draw the three text objects
    draw(menuTitle);
    draw(menuText);
    draw(backText);
}


void Game::drawWinItems (string winMessage)
{
    // Text objects for the win text, the Play again option, the Main menu
    // option and the Quit option
    sf::Text winMessageText;
    sf::Text winPlayAgainText;
    sf::Text winMainMenuText;
    sf::Text winQuitText;

    // Set up the win text
    winMessageText.setFont(_mainFont);
    winMessageText.setString(winMessage);
    winMessageText.setCharacterSize(50);
    winMessageText.setPosition(getSize().x / 2.0f -
                                   winMessageText.getLocalBounds().width / 2.0f
                                   - 5,
                                100);

    // Set up the Play again option
    winPlayAgainText.setFont(_mainFont);
    winPlayAgainText.setString("play again");
    winPlayAgainText.setCharacterSize(40);
    winPlayAgainText.setPosition(getSize().x / 2.0f - 10, getSize().y / 2.0f);

    // Set up the Main menu option
    winMainMenuText.setFont(_mainFont);
    winMainMenuText.setString("main menu");
    winMainMenuText.setCharacterSize(40);
    winMainMenuText.setPosition(getSize().x / 2.0f - 10,
                                getSize().y / 2.0f + 100);

    // Set up the Quit option
    winQuitText.setFont(_mainFont);
    winQuitText.setString("quit");
    winQuitText.setCharacterSize(40);
    winQuitText.setPosition(getSize().x / 2.0f - 10, getSize().y / 2.0f + 200);

    // Draw the four text objects
    draw(winMessageText);
    draw(winPlayAgainText);
    draw(winMainMenuText);
    draw(winQuitText);
}
