#include "Game.hh"

int main (int argc, char *argv[])
{
    Game pong(800, 600, "SFML Pong");

    pong.play();

    return 0;
}
