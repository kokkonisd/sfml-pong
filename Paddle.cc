#include "Paddle.hh"


Paddle::Paddle (float width, float height, float speed)
:
    // Call to super() to initialize the Paddle rectangle
    sf::RectangleShape(sf::Vector2f(width, height)),
    // Set the Paddle's speed
    _speed(speed)
{}


void Paddle::operator++ ()
{
    // Move the Paddle upwards based on its speed
    setPosition(getPosition().x, getPosition().y + _speed);
}


void Paddle::operator-- ()
{
    // Move the Paddle donwards based on its speed
    setPosition(getPosition().x, getPosition().y - _speed);
}
