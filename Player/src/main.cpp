#define ENABLE_REFLECTION 1
#include "catos/reflection.h"
#include "catos/game.h"
#include "core/platform.h"

#include "core/entry_point.h"


typedef void(* PluginEntryPointFn)(catos::Registry& registry);

int main() {

    catos::Registry registry{};

    //game.initializeSystems();

    catos::Platform platform{};

    void* lib = platform.load_shared_library("../../../Resources/test.dll");

    if (lib) {
        PluginEntryPointFn func = (PluginEntryPointFn) platform.get_proc_adress(lib, "catos_entry_point");
        if (func) {
            func(registry);
        } else {
            spdlog::error("Could not find function: {} {}",  (void*) lib, (void*) func);
        }
    } else {
        spdlog::error("Could not load lib");
    }

    platform.free_shared_library(lib);


    //
    // while (game.is_alive()) {
    //     game.update();
    //
    //     game.render();
    // }

    // game.destroySystems();

    return 0;
}

