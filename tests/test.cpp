#define CHESS_DEBUG

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cheats.h>
#include <chess/include.h>

int main() {
    // set random
    srand(time(NULL));

    Chess::Board board;

    board.setFen("rnbqkbnr/8/8/8/p7/N7/7P/1K3qNR w - - 0 1");
    std::vector<Chess::Move> moves = Chess::Generator::getPseudoLegalMoves(board);
    std::cout << board.getFen() << std::endl;
    std::cout << moves.size() << std::endl;

    moves = Chess::Generator::getLegalMoves(board);
    std::cout << "legal:" << moves.size() << std::endl;

    // while (true) {
    //     if (Chess::Generator::isEnd(board)) {
	// 		break;
	// 	}
	// 	std::vector<Chess::Move> moves = Chess::Generator::getLegalMoves(board);
    //     Chess::Move m = moves[0];
    //     // std::cout << m.UCI() << std::endl;
	// 	board.move(m);
    //     std::cout << board.getFen() << std::endl;
	// }

    // std::cout << board.getFen() << std::endl;

    return 0;
}