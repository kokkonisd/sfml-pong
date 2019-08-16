#pragma once

#include <SFML/Graphics.hpp>
#include <stdlib.h>

using namespace std;

/**
 * @brief The Pong class.
 * 
 * The Pong class describes the small square that moves around and bounces off
 * paddles. It handles its speed, direction and size. It inherits the
 * properties of SFML's RectangleShape class.
 */
class Pong: public sf::RectangleShape {

    public:
        // Constructor method
        Pong (float size, float baseSpeed);
        // Initialization method
        void init (float screenWidth, float screenHeight);
        // Methods to flip the direction of the Pong
        void flipDirectionX ();
        void flipDirectionY ();
        // Setters - Getters
        void setSpeedX (float speedX);
        void setSpeedY (float speedY);
        float getSpeedX ();
        float getSpeedY ();
        int getDirectionX ();
        int getDirectionY ();

    private:
        // Direction in the X and Y axis
        int _directionX;
        int _directionY;
        // The Pong's base speed (the speed it has at the start of the round)
        float _baseSpeed;
        // The Pong's current speed
        float _speedX;
        float _speedY;

};
