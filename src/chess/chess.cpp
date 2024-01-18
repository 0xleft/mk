#include "chess.h"

std::vector<Chess::Move> Chess::Board::getLegalMoves() {
    // todo
    return std::vector<Chess::Move>();
}

void Chess::Board::draw() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // TODO
            // EADK::Display::pushRectUniform(EADK::Rect(i * 10, j * 10, 10, 10), (i + j) % 2 == 0 ? EADK::Color(0x000000) : EADK::Color(0xFFFFFF));
        }
    }
}