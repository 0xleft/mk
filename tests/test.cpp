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
    chess::Board board = chess::Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::cout << chess::attacks::RookTable->attacks->count() << std::endl;

    return 0;
}