#include "Pong.hh"


Pong::Pong (float size, float baseSpeed)
:
    // Call super() with the size parameters to create a square
    sf::RectangleShape(sf::Vector2f(size, size)),
    // Set the base speed
    _baseSpeed(baseSpeed)
{}



void Pong::init (float screenWidth, float screenHeight)
{
    // Center the Pong on the screen
    setPosition(screenWidth / 2 - getSize().x / 2,
                screenHeight / 2 - getSize().y / 2);

    // Get a random direction (1 or -1) on both axes
    _directionX = rand() % 2 == 0 ? 1 : -1;
    _directionY = rand() % 2 == 0 ? 1 : -1;
    // Get a random speed (80% or 180% of the base speed) on both axes
    _speedX = (rand() % 2 + 0.8) * _baseSpeed;
    _speedY = (rand() % 2 + 0.8) * _baseSpeed;
}


void Pong::flipDirectionX ()
{
    _directionX = - _directionX;
}


void Pong::flipDirectionY ()
{
    _directionY = - _directionY;
}



void Pong::setSpeedX (float speedX)
{
    _speedX = speedX;
}


void Pong::setSpeedY (float speedY)
{
    _speedY = speedY;
}


float Pong::getSpeedX ()
{
    return _speedX;
}


float Pong::getSpeedY ()
{
    return _speedY;
}


int Pong::getDirectionX ()
{
    return _directionX;
}


int Pong::getDirectionY ()
{
    return _directionY;
}
