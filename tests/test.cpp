#define CHESS_DEBUG

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cheats.h>
#include <chess/include.h>

int perf(Chess::Board& board, int depth) {
    if (depth == 0) {
        return 1;
    }

    int count = 0;
    std::vector<Chess::Move> moves = Chess::Generator::getLegalMoves(board);
    for (Chess::Move move : moves) {
        board.move(move);
        count += perf(board, depth - 1);
        board.undo();
    }

    return count;
}

int main() {
    // set random
    srand(time(NULL));

    Chess::Board board;
    std::cout << "Perft 1: " << perf(board, 1) << std::endl;
    Chess::Board board2;
    std::cout << "Perft 2: " << perf(board2, 2) << std::endl;
    Chess::Board board3;
    std::cout << "Perft 3: " << perf(board3, 3) << std::endl;
    Chess::Board board4;
    std::cout << "Perft 4: " << perf(board4, 4) << std::endl;
    Chess::Board board5;
    std::cout << "Perft 5: " << perf(board5, 5) << std::endl;
    Chess::Board board6;
    std::cout << "Perft 6: " << perf(board6, 6) << std::endl;

    return 0;
}