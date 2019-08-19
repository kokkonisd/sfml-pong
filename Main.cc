#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Game.hh"
#include "Menu.hh"

int main (int argc, char *argv[])
{
    // Initialize the random seed
    srand(time(NULL));

    // Initialize a new game
    Game pong(800, 600, "SFML Pong");

    // Show the main menu
    pong.mainMenu();

    return 0;
}
