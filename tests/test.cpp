#include <cheats.h>
#include <chess/src/include.hpp>

using namespace chess;

int main(int argc, char* argv[]) {
    Board board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    Movelist moves;
    movegen::legalmoves(moves, board);

    if (moves.size() != 20) {
        std::cout << "Moves are wrong" << std::endl;
    }

	return 0;
}