#pragma once

#include <SFML/Graphics.hpp>
#include <stdlib.h>     /* srand, rand */

using namespace std;

class Pong: public sf::RectangleShape {

    public:
        Pong (float size, float baseSpeed);
        void init (float screenWidth, float screenHeight);
        void flipDirectionX ();
        void flipDirectionY ();
        void setSpeedX (float speedX);
        void setSpeedY (float speedY);
        float getSpeedX ();
        float getSpeedY ();
        int getDirectionX ();
        int getDirectionY ();

    private:
        int _directionX;
        int _directionY;
        float _baseSpeed;
        float _speedX;
        float _speedY;

};
