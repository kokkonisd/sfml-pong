/**
 * @file Game.hh
 * @author Dimitri Kokkonis ([\@kokkonisd](https://github.com/kokkonisd))
 * @date 8 Feb 2019
 * @brief The main game logic for the Pong game.
 */

#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

#include "Paddle.hh"
#include "Pong.hh"

using std::string;


/**
 * @brief The Game class.
 * 
 * This class handles the Pong game, from controlling menus to operating the
 * game's logic.
 */
class Game: public sf::RenderWindow {

    public:
        /**
         * @brief The constructor method for the Game object.
         * 
         * The constructor initializes the Game with the right variables and
         * loads assets (such as fonts). It inherits properties from SFML's
         * RenderWindow class because it contains one window in which the game
         * is played.
         *
         * @param[in]  width   The width of the Game window
         * @param[in]  height  The height of the Game window
         * @param[in]  title   The title of the Game window
         */
        Game (int width, int height, string title);
        /**
         * @brief Displays the main menu.
         * 
         * This method creates and displays the main menu of the game, allowing
         * the user to choose between launching the game, seeing the controls
         * or the credits and quitting the game.
         */
        void mainMenu ();
        /**
         * @brief Displays the controls menu.
         * 
         * This method creates and displays the controls menu of the game,
         * which explains to the user how the game is supposed to be played.
         */
        void controlsMenu ();
        /**
         * @brief Displays the credits menu.
         * 
         * This method creates and displays the credits menu of the game, which
         * lets the user know when and by whom the game was made.
         */
        void creditsMenu ();

        /** The Paddle's speed */
        static float PADDLE_SPEED;
        /** The base speed (or starting speed) of the Pong */
        static float PONG_BASE_SPEED;
        /** The Pong's speed multiplier on the X axis */
        static float PONG_SPEED_MULTIPLIER_X;
        /** The Pong's speed multiplier on the Y axis */
        static float PONG_SPEED_MULTIPLIER_Y;


    private:
        /**
         * @brief Launches a game of Pong.
         * 
         * This method launches a game of Pong, resetting all the variables at
         * the start (the position of the Paddles and of the Pong, the point
         * counters etc) and displays a "pause screen" at the start, allowing
         * the players to prepare themselves before the start of the game.
         */
        void play ();
        /**
         * @brief Shows the win screen of the game.
         * 
         * This method is called at the end of a game of Pong, when one of the
         * players reaches a score of 11. It displays the score, a win message
         * and a win menu that allows the players to launch a new game, return
         * to the main menu or quit the game.
         *
         * @param[in]  winMessage  The win message, which depends on which
         *                         player won the game.
         */
        void win (string winMessage);
        /**
         * @brief Sets the up and down movement flags of both Paddles to the
         * boolean value passed in as an argument.
         * 
         * When a key is pressed, its flag is set to true, and when it is 
         * released, it is set to false. This allows proper handling of the
         * movement of the Paddles.
         *
         * @param[in]  keyCode       The key code.
         * @param[in]  isKeyPressed  Indicates if the key is pressed.
         */
        void handleMoveKeyEvent (int keyCode, bool isKeyPressed);
        /**
         * @brief Handles the movement of the Paddles.
         * 
         * This method moves the Paddles according to their current positions 
         * and their movement flags.
         */
        void handlePaddleMovement ();
        /**
         * @brief Handles the Pong's movement.
         * 
         * This method moves the Pong based on its current speed and direction.
         * If it hits the top or the bottom of the screen or one of the Paddles
         * then it flips its direction accordingly; if it hits the left or
         * the right side of the screen without hitting the Paddles, then the
         * point counters are incremented accordingly and the Pong's position,
         * speed and direction are reset.
         */
        void handlePongMovement ();
        /**
         * @brief Updates and draws the score text.
         * 
         * This method builds a string based on the current scores of both
         * sides, then draws that string near the top of the screen in the
         * format of `X - Y`.
         */
        void handleScoreText ();
        /**
         * @brief Draws the pre-game text on the screen.
         * 
         * This method draws a message on the screen while the game is 
         * paused to notify players that they need to press the Spacebar in
         * order to start the game.
         */
        void handlePreGameText ();


        /** The left Paddle object. */
        Paddle _leftPaddle;
        /** The right Paddle object. */
        Paddle _rightPaddle;
        /** The Pong object. */
        Pong _pong;

        /** The Pong's speed multiplier for the X axis. */
        float _pongSpeedMultiplierX;
        /** The Pong's speed multiplier for the Y axis. */
        float _pongSpeedMultiplierY;

        /** The UP movement flag for the left Paddle. */
        bool _upFlagLeft;
        /** The DOWN movement flag for the left Paddle */
        bool _downFlagLeft;
        /** The UP movement flag for the right Paddle. */
        bool _upFlagRight;
        /** The DOWN movement flag for the right Paddle */
        bool _downFlagRight;

        /** The point counter for the left Paddle. */
        int _leftPoints;
        /** The point counter for the right Paddle. */
        int _rightPoints;

        /** The game's main font object. */
        sf::Font _mainFont;

};
