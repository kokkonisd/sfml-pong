#pragma once

#include <SFML/Graphics.hpp>
#include <string>

using namespace std;

class Paddle: public sf::RectangleShape {

    public:
        Paddle (float width, float height, float speed);
        void operator++ ();
        void operator-- ();

    private:
        float _speed;
};
