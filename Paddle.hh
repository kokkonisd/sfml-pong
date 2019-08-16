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
        // The constructor method
        Paddle (float width, float height, float speed);
        // Operator overrides for the ++ and -- operators
        void operator++ ();
        void operator-- ();

    private:
        // The Paddle's speed
        float _speed;
};
