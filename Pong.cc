#include "Pong.hh"

/**
 * @brief The constructor method for the Pong object.
 *
 * @param[in]  size       The Pong's size (it's a square).
 * @param[in]  baseSpeed  The Pong's base speed (at which it will travel at the
 *                        start of each round)
 */
Pong::Pong (float size, float baseSpeed)
:
    // Call super() with the size parameters to create a square
    sf::RectangleShape(sf::Vector2f(size, size)),
    // Set the base speed
    _baseSpeed(baseSpeed)
{}


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


/**
 * @brief Flips the direction of the Pong on the X axis.
 */
void Pong::flipDirectionX ()
{
    _directionX = - _directionX;
}


/**
 * @brief Flips the direction of the Pong on the Y axis.
 */
void Pong::flipDirectionY ()
{
    _directionY = - _directionY;
}


/**
 * @brief Sets the Pong's speed on the X axis.
 *
 * @param[in]  speedX  The Pong's speed on the X axis.
 */
void Pong::setSpeedX (float speedX)
{
    _speedX = speedX;
}


/**
 * @brief Sets the Pong's speed on the Y axis.
 *
 * @param[in]  speedY  The Pong's speed on the Y axis.
 */
void Pong::setSpeedY (float speedY)
{
    _speedY = speedY;
}


/**
 * @brief Gets the Pong's speed on the X axis.
 *
 * @return     The Pong's speed on the X axis.
 */
float Pong::getSpeedX ()
{
    return _speedX;
}


/**
 * @brief Gets the Pong's speed on the Y axis.
 *
 * @return     The Pong's speed on the Y axis.
 */
float Pong::getSpeedY ()
{
    return _speedY;
}


/**
 * @brief Gets the Pong's direction on the X axis.
 *
 * @return     The Pong's direction on the X axis.
 */
int Pong::getDirectionX ()
{
    return _directionX;
}


/**
 * @brief Gets the Pong's direction on the Y axis.
 *
 * @return     The Pong's direction on the Y axis.
 */
int Pong::getDirectionY ()
{
    return _directionY;
}
