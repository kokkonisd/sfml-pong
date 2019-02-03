#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Pong: public sf::RectangleShape {

    public:
        Pong (float width, float height, float speed);
        void operator++ ();
        void operator-- ();

    private:
        float _speed;
};
