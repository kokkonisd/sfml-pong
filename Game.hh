#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Game: public sf::RenderWindow {

    public:
        Game (int width, int height, string title);
        void play ();

    private:
        sf::RectangleShape _leftPong;
        sf::RectangleShape _rightPong;
        float _pongHeight;
        float _pongWidth;

};
