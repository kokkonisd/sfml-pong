#include "Pong.hh"

Pong::Pong (float size, float baseSpeed)
:
    sf::RectangleShape(sf::Vector2f(size, size)),
    _speed(baseSpeed)
{}


void Pong::init (float screenWidth, float screenHeight)
{
    setPosition(screenWidth / 2 - getSize().x / 2, screenHeight / 2 - getSize().y / 2);
    
    _directionX = rand() % 2 == 0 ? 1 : -1;
    _directionY = rand() % 2 == 0 ? 1 : -1;
}
