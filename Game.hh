#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Paddle.hh"

using namespace std;

class Game: public sf::RenderWindow {

    public:
        Game (int width, int height, string title);
        void play ();

    private:
        void handleMoveKeyEvent (int keyCode, bool isKeyPressed);
        void handlePaddleMovement ();

        Paddle _leftPaddle;
        Paddle _rightPaddle;

        bool upFlagLeft;
        bool downFlagLeft;
        bool upFlagRight;
        bool downFlagRight;

};
