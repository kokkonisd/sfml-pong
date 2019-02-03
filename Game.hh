#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "Pong.hh"

using namespace std;

class Game: public sf::RenderWindow {

    public:
        Game (int width, int height, string title);
        void play ();

    private:
        void handleMoveKeyEvent (int keyCode, bool isKeyPressed);

        Pong _leftPong;
        Pong _rightPong;

        bool upFlagLeft;
        bool downFlagLeft;
        bool upFlagRight;
        bool downFlagRight;

};
