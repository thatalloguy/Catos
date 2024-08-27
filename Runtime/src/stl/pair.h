//
// Created by allos on 8/27/2024.
//

#ifndef CATOS_PAIR_H
#define CATOS_PAIR_H


namespace catos {

    ///Simple struct to hold 2 objects.
    template<typename K, typename V>
    struct Pair {
        K first;
        V second;
    };

}




#endif //CATOS_PAIR_H
