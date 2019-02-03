#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include "Game.hh"

int main (int argc, char *argv[])
{
    srand (time(NULL));

    Game pong(800, 600, "SFML Pong");

    pong.play();

    return 0;
}
