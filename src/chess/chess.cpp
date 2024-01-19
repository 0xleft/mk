#include "chess.h"

std::vector<Chess::Move> Chess::Board::getLegalMoves() {
    std::vector<Chess::Move> moves;
    std::vector<Chess::Move> toAddMoves;

    // not really efficient // todo optimize
    for (int i = 0; i < 8; i++) {
        for (int j = 0; i < 8; i++) {
            Chess::Square* square = this->getSquare(i, j);
            if (square->getPiece() == EMPTY) continue;
            if (square->getColor() != turn) continue;
            switch (square->getPiece()) {
                case PAWN:
                    toAddMoves = getLegalMovesPawn(i, j);
                    moves.insert(moves.end(), toAddMoves.begin(), toAddMoves.end());
                    break;
                case ROOK:
                    toAddMoves = getLegalMovesRook(i, j);
                    moves.insert(moves.end(), toAddMoves.begin(), toAddMoves.end());                    
                    break;
                case KNIGHT:
                    toAddMoves = getLegalMovesKnight(i, j);
                    moves.insert(moves.end(), toAddMoves.begin(), toAddMoves.end());
                    break;
                case BISHOP:
                    toAddMoves = getLegalMovesBishop(i, j);
                    moves.insert(moves.end(), toAddMoves.begin(), toAddMoves.end());
                    break;
                case QUEEN:
                    toAddMoves = getLegalMovesQueen(i, j);
                    moves.insert(moves.end(), toAddMoves.begin(), toAddMoves.end());
                    break;
                case KING:
                    toAddMoves = getLegalMovesKing(i, j);
                    moves.insert(moves.end(), toAddMoves.begin(), toAddMoves.end());
                    break;
            }
        }
    }

    return moves;
}

std::vector<Chess::Move> Chess::Board::getLegalMovesPawn(int x, int y) {
    std::vector<Chess::Move> moves;
    Chess::Square* square = this->getSquare(x, y);
    if (square->getColor() == WHITE) {
        if (y == 1) {
            if (this->getSquare(x, y + 1)->getPiece() == EMPTY) {
                moves.push_back(Chess::Move(x, y, x, y + 1));
                if (this->getSquare(x, y + 2)->getPiece() == EMPTY) {
                    moves.push_back(Chess::Move(x, y, x, y + 2));
                }
            }
        } else {
            if (this->getSquare(x, y + 1)->getPiece() == EMPTY) {
                moves.push_back(Chess::Move(x, y, x, y + 1));
            }
        }
        if (this->getSquare(x + 1, y + 1)->getColor() == BLACK) {
            moves.push_back(Chess::Move(x, y, x + 1, y + 1));
        }
        if (this->getSquare(x - 1, y + 1)->getColor() == BLACK) {
            moves.push_back(Chess::Move(x, y, x - 1, y + 1));
        }
        if (lastMove.getY1() == 1 && lastMove.getY2() == 3 && lastMove.getX2() == x + 1) {
            moves.push_back(Chess::Move(x, y, x + 1, y + 1));
        }
        if (lastMove.getY1() == 1 && lastMove.getY2() == 3 && lastMove.getX2() == x - 1) {
            moves.push_back(Chess::Move(x, y, x - 1, y + 1));
        }
    } else {
        if (y == 6) {
            if (this->getSquare(x, y - 1)->getPiece() == EMPTY) {
                moves.push_back(Chess::Move(x, y, x, y - 1));
                if (this->getSquare(x, y - 2)->getPiece() == EMPTY) {
                    moves.push_back(Chess::Move(x, y, x, y - 2));
                }
            }
        } else {
            if (this->getSquare(x, y - 1)->getPiece() == EMPTY) {
                moves.push_back(Chess::Move(x, y, x, y - 1));
            }
        }
        if (this->getSquare(x + 1, y - 1)->getColor() == WHITE) {
            moves.push_back(Chess::Move(x, y, x + 1, y - 1));
        }
        if (this->getSquare(x - 1, y - 1)->getColor() == WHITE) {
            moves.push_back(Chess::Move(x, y, x - 1, y - 1));
        }
        if (lastMove.getY1() == 6 && lastMove.getY2() == 4 && lastMove.getX2() == x + 1) {
            moves.push_back(Chess::Move(x, y, x + 1, y - 1));
        }
        if (lastMove.getY1() == 6 && lastMove.getY2() == 4 && lastMove.getX2() == x - 1) {
            moves.push_back(Chess::Move(x, y, x - 1, y - 1));
        }
    }

    return moves;
}

std::vector<Chess::Move> Chess::Board::getLegalMovesRook(int x, int y) {
    std::vector<Chess::Move> moves;
    Chess::Square* square = this->getSquare(x, y);
    for (int i = x + 1; i < 8; i++) {
        if (this->getSquare(i, y)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, i, y));
        } else {
            if (this->getSquare(i, y)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, i, y));
            }
            break;
        }
    }
    for (int i = x - 1; i >= 0; i--) {
        if (this->getSquare(i, y)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, i, y));
        } else {
            if (this->getSquare(i, y)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, i, y));
            }
            break;
        }
    }
    for (int i = y + 1; i < 8; i++) {
        if (this->getSquare(x, i)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x, i));
        } else {
            if (this->getSquare(x, i)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x, i));
            }
            break;
        }
    }
    for (int i = y - 1; i >= 0; i--) {
        if (this->getSquare(x, i)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x, i));
        } else {
            if (this->getSquare(x, i)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x, i));
            }
            break;
        }
    }
    return moves;
}

std::vector<Chess::Move> Chess::Board::getLegalMovesBishop(int x, int y) {
    std::vector<Chess::Move> moves;
    Chess::Square* square = this->getSquare(x, y);
    for (int i = x + 1, j = y + 1; i < 8 && j < 8; i++, j++) {
        if (this->getSquare(i, j)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, i, j));
        } else {
            if (this->getSquare(i, j)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, i, j));
            }
            break;
        }
    }
    for (int i = x - 1, j = y + 1; i >= 0 && j < 8; i--, j++) {
        if (this->getSquare(i, j)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, i, j));
        } else {
            if (this->getSquare(i, j)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, i, j));
            }
            break;
        }
    }
    for (int i = x + 1, j = y - 1; i < 8 && j >= 0; i++, j--) {
        if (this->getSquare(i, j)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, i, j));
        } else {
            if (this->getSquare(i, j)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, i, j));
            }
            break;
        }
    }
    for (int i = x - 1, j = y - 1; i >= 0 && j >= 0; i--, j--) {
        if (this->getSquare(i, j)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, i, j));
        } else {
            if (this->getSquare(i, j)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, i, j));
            }
            break;
        }
    }
    return moves;
}

std::vector<Chess::Move> Chess::Board::getLegalMovesKnight(int x, int y) {
    std::vector<Chess::Move> moves;
    Chess::Square* square = this->getSquare(x, y);
    if (x + 2 < 8 && y + 1 < 8) {
        if (this->getSquare(x + 2, y + 1)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x + 2, y + 1));
        } else {
            if (this->getSquare(x + 2, y + 1)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x + 2, y + 1));
            }
        }
    }
    if (x + 2 < 8 && y - 1 >= 0) {
        if (this->getSquare(x + 2, y - 1)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x + 2, y - 1));
        } else {
            if (this->getSquare(x + 2, y - 1)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x + 2, y - 1));
            }
        }
    }
    if (x - 2 >= 0 && y + 1 < 8) {
        if (this->getSquare(x - 2, y + 1)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x - 2, y + 1));
        } else {
            if (this->getSquare(x - 2, y + 1)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x - 2, y + 1));
            }
        }
    }
    if (x - 2 >= 0 && y - 1 >= 0) {
        if (this->getSquare(x - 2, y - 1)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x - 2, y - 1));
        } else {
            if (this->getSquare(x - 2, y - 1)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x - 2, y - 1));
            }
        }
    }
    if (x + 1 < 8 && y + 2 < 8) {
        if (this->getSquare(x + 1, y + 2)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x + 1, y + 2));
        } else {
            if (this->getSquare(x + 1, y + 2)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x + 1, y + 2));
            }
        }
    }
    if (x + 1 < 8 && y - 2 >= 0) {
        if (this->getSquare(x + 1, y - 2)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x + 1, y - 2));
        } else {
            if (this->getSquare(x + 1, y - 2)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x + 1, y - 2));
            }
        }
    }
    if (x - 1 >= 0 && y + 2 < 8) {
        if (this->getSquare(x - 1, y + 2)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x - 1, y + 2));
        } else {
            if (this->getSquare(x - 1, y + 2)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x - 1, y + 2));
            }
        }
    }
    if (x - 1 >= 0 && y - 2 >= 0) {
        if (this->getSquare(x - 1, y - 2)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x - 1, y - 2));
        } else {
            if (this->getSquare(x - 1, y - 2)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x - 1, y - 2));
            }
        }
    }

    return moves;
}

std::vector<Chess::Move> Chess::Board::getLegalMovesQueen(int x, int y) {
    std::vector<Chess::Move> moves;
    std::vector<Chess::Move> toAddMoves;
    toAddMoves = getLegalMovesRook(x, y);
    moves.insert(moves.end(), toAddMoves.begin(), toAddMoves.end());
    toAddMoves = getLegalMovesBishop(x, y);
    moves.insert(moves.end(), toAddMoves.begin(), toAddMoves.end());
    return moves;
}

std::vector<Chess::Move> Chess::Board::getLegalMovesKing(int x, int y) {
    std::vector<Chess::Move> moves;
    Chess::Square* square = this->getSquare(x, y);
    if (x + 1 < 8) {
        if (this->getSquare(x + 1, y)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x + 1, y));
        } else {
            if (this->getSquare(x + 1, y)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x + 1, y));
            }
        }
    }
    if (x - 1 >= 0) {
        if (this->getSquare(x - 1, y)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x - 1, y));
        } else {
            if (this->getSquare(x - 1, y)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x - 1, y));
            }
        }
    }
    if (y + 1 < 8) {
        if (this->getSquare(x, y + 1)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x, y + 1));
        } else {
            if (this->getSquare(x, y + 1)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x, y + 1));
            }
        }
    }
    if (y - 1 >= 0) {
        if (this->getSquare(x, y - 1)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x, y - 1));
        } else {
            if (this->getSquare(x, y - 1)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x, y - 1));
            }
        }
    }
    if (x + 1 < 8 && y + 1 < 8) {
        if (this->getSquare(x + 1, y + 1)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x + 1, y + 1));
        } else {
            if (this->getSquare(x + 1, y + 1)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x + 1, y + 1));
            }
        }
    }
    if (x + 1 < 8 && y - 1 >= 0) {
        if (this->getSquare(x + 1, y - 1)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x + 1, y - 1));
        } else {
            if (this->getSquare(x + 1, y - 1)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x + 1, y - 1));
            }
        }
    }
    if (x - 1 >= 0 && y + 1 < 8) {
        if (this->getSquare(x - 1, y + 1)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x - 1, y + 1));
        } else {
            if (this->getSquare(x - 1, y + 1)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x - 1, y + 1));
            }
        }
    }
    if (x - 1 >= 0 && y - 1 >= 0) {
        if (this->getSquare(x - 1, y - 1)->getPiece() == EMPTY) {
            moves.push_back(Chess::Move(x, y, x - 1, y - 1));
        } else {
            if (this->getSquare(x - 1, y - 1)->getColor() != square->getColor()) {
                moves.push_back(Chess::Move(x, y, x - 1, y - 1));
            }
        }
    }

    return moves;
}

void Chess::Board::draw() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            // TODO
            // EADK::Display::pushRectUniform(EADK::Rect(i * 10, j * 10, 10, 10), (i + j) % 2 == 0 ? EADK::Color(0x000000) : EADK::Color(0xFFFFFF));
        }
    }
}