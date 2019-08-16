#pragma once

#include <SFML/Graphics.hpp>

using namespace std;

/**
 * @brief The Paddle class.
 * 
 * This class describes the Paddle object, which is what the user controls in
 * order to deflect the Pong and gain points. It inherits properties from 
 * SFML's RectangleShape class, as it is basically a rectangle.
 */
class Paddle: public sf::RectangleShape {

    public:
        /**
         * @brief The Paddle constructor method.
         *
         * @param[in]  width   The width of the Paddle
         * @param[in]  height  The height of the Paddle
         * @param[in]  speed   The speed of the Paddle
         */
        Paddle (float width, float height, float speed);
        /**
         * @brief ++ operator override to move the paddle based on its speed
         */
        void operator++ ();
        /**
         * @brief -- operator override to move the paddle based on its speed
         */
        void operator-- ();


    private:
        /** The Paddle's speed. */
        float _speed;
};
