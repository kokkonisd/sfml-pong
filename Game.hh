#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

#include "Paddle.hh"
#include "Pong.hh"

using namespace std;

class Game: public sf::RenderWindow {

    public:
        Game (int width, int height, string title);
        void menu ();
        // void win (string winMessage);

        static float PADDLE_SPEED;
        static float PONG_BASE_SPEED;
        static float PONG_SPEED_MULTIPLIER_X;
        static float PONG_SPEED_MULTIPLIER_Y;

    private:
        void play ();
        void win (string winMessage);
        void handleMoveKeyEvent (int keyCode, bool isKeyPressed);
        void handlePaddleMovement ();
        void handlePongMovement ();
        void handleScoreText ();
        void handlePreGameText ();
        void drawMenuItems ();
        void drawControlsItems ();
        void drawCreditsItems ();
        void drawWinItems (string winMessage);


        Paddle _leftPaddle;
        Paddle _rightPaddle;
        Pong _pong;

        float _pongSpeedMultiplierX;
        float _pongSpeedMultiplierY;

        bool _upFlagLeft;
        bool _downFlagLeft;
        bool _upFlagRight;
        bool _downFlagRight;

        int _leftPoints;
        int _rightPoints;

        sf::Font _mainFont;

};
