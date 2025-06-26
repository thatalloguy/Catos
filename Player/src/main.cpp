#define ENABLE_REFLECTION 1
#include "catos/reflection.h"
#include "catos/game.h"

int main() {
    catos::game game{{""}};
    catos::registerTypes(game.get<catos::Registry>());


    game.initializeSystems();

    while (game.is_alive()) {
        game.update();

        game.render();
    }

    game.destroySystems();

    return 0;
}

