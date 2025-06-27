//
// Created by allos on 27/06/2025.
//
#pragma once

#include "types.h"

namespace catos {
    struct Registry;
}


#ifdef __cplusplus
extern "C" {
#endif

    CATOS_API void catos_entry_point(catos::Registry& registry);


#ifdef __cplusplus
}
#endif