#define ENABLE_REFLECTION 1
#include "catos/reflection.h"
#include "catos/game.h"
#include "core/platform.h"

#include "core/entry_point.h"

#include <direct.h>

int main() {


    catos::Registry registry{};

    catos::Game game{
        catos::GameCreationInfo{
            "../../../Resources/test.dll"
        },
        registry
    };


    game.initializeSystems();
    game.loadProject();




    while (game.is_alive()) {
        game.update();

        game.render();
    }

    game.destroySystems();

    return 0;
}

