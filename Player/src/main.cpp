#include "catos/Game.h"

int main() {

    catos::Game game{{""}};

    game.initializeSystems();

    while (game.is_alive()) {
        game.update();

        game.render();
    }

    game.destroySystems();

    return 0;
}

