#define CHESS_DEBUG

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cheats.h>
//#include <engine/evaluator.h>
#include <chess/src/include.hpp>

int main() {
    chess::Board board = chess::Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
    std::cout << sizeof(chess::attacks::BishopAttacks[0]) << std::endl;

    chess::Movelist moves;
    chess::movegen::legalmoves(moves, board);
    std::cout << moves.size();

    return 0;
}