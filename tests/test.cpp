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

    return 0;
}