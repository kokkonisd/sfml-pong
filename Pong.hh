#pragma once

#include <SFML/Graphics.hpp>
#include <stdlib.h>     /* srand, rand */

using namespace std;

class Pong: public sf::RectangleShape {

    public:
        Pong (float size, float baseSpeed);
        void init (float screenWidth, float screenHeight);

        int _directionX;
        int _directionY;
        float _speedX;
        float _speedY;

    private:
        float _baseSpeed;

};
