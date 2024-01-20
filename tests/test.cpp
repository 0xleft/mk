#define CHESS_DEBUG

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cheats.h>
#include <chess/include.h>

int main() {

    Chess::Board board;
    std::vector<Chess::Move> moves = Chess::Generator::getLegalMoves(board);
    std::cout << moves.size() << std::endl;

    // board.setFen("rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2");

    while (!Chess::Generator::isEnd(board)) {
        std::vector<Chess::Move> moves = Chess::Generator::getLegalMoves(board);
        Chess::Move m = moves[0];
        board.move(m);
        //board.printBoard();
        //std::cout << "Legal moves: " << moves.size() << std::endl;
        //std::cout << "Is end?: " << Chess::Generator::isEnd(board) << std::endl;
    }

    return 0;
}