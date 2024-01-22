#define CHESS_DEBUG

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cheats.h>
//#include <engine/evaluator.h>
#include <chess/src/bitboard.hpp>

using U64 = std::uint64_t;
struct Magic {
    U64 mask;
    U64 magic;
    chess::Bitboard attacks[4096];
    U64 shift;
};

namespace chess {
    namespace attacks {
        Magic BishopTable[64] = {};
        Magic RookTable[64] = {};
    }
}

#include "../pregenerator/hdmagics/hdmagics.hpp"

int main() {
    std::cout << chess::attacks::BishopTable[0].attacks[0] << std::endl;
    return 0;
}