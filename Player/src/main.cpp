#include "catos/game.h"

int main() {

    catos::game game{{""}};

    game.initializeSystems();

    while (game.is_alive()) {
        game.update();

        game.render();
    }

    game.destroySystems();

    return 0;
}

