#define CHESS_DEBUG

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cheats.h>
#include <engine/evaluator.h>

int main() {
    // set random
    Chess::Board board;
    while (!Chess::Generator::isEnd(board)) {
        Chess::Move move = Evaluator::getBestMove(board);
        board.move(move);
        std::cout << board.getFen() << std::endl;
    }

    return 0;
}