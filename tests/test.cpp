#define CHESS_DEBUG

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cheats.h>
#include <engine/evaluator.h>
#include <chess/src/include.hpp>

int main() {
    // set random
    for (int i = 0; i < 64; i++) {
        chess::attacks::Magic c = chess::attacks::BishopTable[i];
        std::cout << "magic: " << c.magic << " mask: " << c.mask << " shift: " << c.shift << std::endl;
        for (int j = 0; j < 4096; j++) {
            c.attacks[j];
        }
    }

    return 0;
}