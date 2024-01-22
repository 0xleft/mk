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
    chess::Board board = chess::Board(chess::constants::STARTPOS);
        std::cout << chess::attacks::BishopTable[63].attacks[0];
    

    return 0;
}
