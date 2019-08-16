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
        /**
         * @brief The constructor method for the Pong object.
         *
         * @param[in]  size       The Pong's size (it's a square).
         * @param[in]  baseSpeed  The Pong's base speed (at which it will travel at the
         *                        start of each round)
         */
        Pong (float size, float baseSpeed);
        /**
         * @brief Centers the Pong on the screen and initializes its direction and
         * speed.
         * 
         * The initialization of the Pong's direction and speed involves some
         * randomness; more specifically, the direction on both the X and the Y axes
         * is randomly set (1 to move towards the right or the bottom, -1 to move
         * towards the left or the top), as is the speed, which is based on the 
         * following formula:
         * 
         * `speed = ((0 or 1) + 0.8) * _baseSpeed`
         * 
         * which means that the Pong will move with a speed between 80% and 180% of the
         * base speed in either direction.
         * 
         * Finally, the Pong's position is set based on the dimensions of the screen
         * as specified by the arguments of the method.
         *
         * @param[in]  screenWidth   The screen width
         * @param[in]  screenHeight  The screen height
         */
        void init (float screenWidth, float screenHeight);
        /**
         * @brief Flips the direction of the Pong on the X axis.
         */
        void flipDirectionX ();
        /**
         * @brief Flips the direction of the Pong on the Y axis.
         */
        void flipDirectionY ();
        
        /**
         * @brief Sets the Pong's speed on the X axis.
         *
         * @param[in]  speedX  The Pong's speed on the X axis.
         */
        void setSpeedX (float speedX);
        /**
         * @brief Sets the Pong's speed on the Y axis.
         *
         * @param[in]  speedY  The Pong's speed on the Y axis.
         */
        void setSpeedY (float speedY);
        /**
         * @brief Gets the Pong's speed on the X axis.
         *
         * @return     The Pong's speed on the X axis.
         */
        float getSpeedX ();
        /**
         * @brief Gets the Pong's speed on the Y axis.
         *
         * @return     The Pong's speed on the Y axis.
         */
        float getSpeedY ();
        /**
         * @brief Gets the Pong's direction on the X axis.
         *
         * @return     The Pong's direction on the X axis.
         */
        int getDirectionX ();
        /**
         * @brief Gets the Pong's direction on the Y axis.
         *
         * @return     The Pong's direction on the Y axis.
         */
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
