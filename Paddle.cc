#include "Paddle.hh"

Paddle::Paddle (float width, float height, float speed)
:
    sf::RectangleShape(sf::Vector2f(width, height)),
    _speed(speed)
{}


void Paddle::operator++ ()
{
    setPosition(getPosition().x, getPosition().y + _speed);
}


void Paddle::operator-- ()
{
    setPosition(getPosition().x, getPosition().y - _speed);
}
