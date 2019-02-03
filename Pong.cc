#include "Pong.hh"

Pong::Pong (float width, float height, float speed)
:
    sf::RectangleShape(sf::Vector2f(width, height)),
    _speed(speed)
{}


void Pong::operator++ ()
{
    setPosition(getPosition().x, getPosition().y + _speed);
}


void Pong::operator-- ()
{
    setPosition(getPosition().x, getPosition().y - _speed);
}
