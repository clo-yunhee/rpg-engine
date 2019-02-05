#include "constants.h"
#include "Game.h"
#include "States/MapExample.h"

int main()
{
    Game game(
            WINDOW_WIDTH,
            WINDOW_HEIGHT,
            WINDOW_TITLE,
            WINDOW_FRAMERATE
    );

    game.pushState(new MapExample);

    game.start();

    game.join();

    return EXIT_SUCCESS;
}
