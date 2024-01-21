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

    chess::Movelist moves;
    chess::movegen::legalmoves(moves, board);
    std::cout << moves.size() << std::endl;

    return 0;
}