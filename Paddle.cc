#include "Paddle.hh"


/**
 * @brief The Paddle constructor method.
 *
 * @param[in]  width   The width of the Paddle
 * @param[in]  height  The height of the Paddle
 * @param[in]  speed   The speed of the Paddle
 */
Paddle::Paddle (float width, float height, float speed)
:
    // Call to super() to initialize the Paddle rectangle
    sf::RectangleShape(sf::Vector2f(width, height)),
    // Set the Paddle's speed
    _speed(speed)
{}


/**
 * @brief ++ operator override to move the paddle based on its speed
 */
void Paddle::operator++ ()
{
    setPosition(getPosition().x, getPosition().y + _speed);
}


/**
 * @brief -- operator override to move the paddle based on its speed
 */
void Paddle::operator-- ()
{
    setPosition(getPosition().x, getPosition().y - _speed);
}
