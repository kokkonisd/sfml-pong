#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Paddle.hh"
#include "Pong.hh"

using namespace std;

class Game: public sf::RenderWindow {

    public:
        Game (int width, int height, string title);
        void play ();

    private:
        void handleMoveKeyEvent (int keyCode, bool isKeyPressed);
        void handlePaddleMovement ();
        void handlePongMovement ();

        Paddle _leftPaddle;
        Paddle _rightPaddle;
        Pong _pong;

        bool _upFlagLeft;
        bool _downFlagLeft;
        bool _upFlagRight;
        bool _downFlagRight;

        int _leftPoints;
        int _rightPoints;

};
