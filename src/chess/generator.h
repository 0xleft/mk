#pragma once

#include "chess.h"

// there are probably a lot of missing moves here so if you down to improve this, please do
// todo rewrite this to use bitboards

namespace Chess {
    namespace Generator {
        std::vector<Move> getDiagonalMoves(Board& board, int x, int y) {
            std::vector<Move> moves;
            Color color = board.getSquare(x, y)->getColor();
            int i = 1;
            while (x + i < 8 && y + i < 8) {
                if (board.getSquare(x + i, y + i)->getColor() == color) {
                    break;
                }
                moves.push_back(Move(x, y, x + i, y + i));
                if (board.getSquare(x + i, y + i)->getColor() != Color::NONE) {
                    break;
                }
                i++;
            }
            i = 1;
            while (x - i >= 0 && y - i >= 0) {
                if (board.getSquare(x - i, y - i)->getColor() == color) {
                    break;
                }
                moves.push_back(Move(x, y, x - i, y - i));
                if (board.getSquare(x - i, y - i)->getColor() != Color::NONE) {
                    break;
                }
                i++;
            }
            i = 1;
            while (x + i < 8 && y - i >= 0) {
                if (board.getSquare(x + i, y - i)->getColor() == color) {
                    break;
                }
                moves.push_back(Move(x, y, x + i, y - i));
                if (board.getSquare(x + i, y - i)->getColor() != Color::NONE) {
                    break;
                }
                i++;
            }
            i = 1;
            while (x - i >= 0 && y + i < 8) {
                if (board.getSquare(x - i, y + i)->getColor() == color) {
                    break;
                }
                moves.push_back(Move(x, y, x - i, y + i));
                if (board.getSquare(x - i, y + i)->getColor() != Color::NONE) {
                    break;
                }
                i++;
            }
            return moves;
        };

        std::vector<Move> getStraightMoves(Board& board, int x, int y) {
            std::vector<Move> moves;
            Color color = board.getSquare(x, y)->getColor();
            for (int i = x + 1; i < 8; i++) {
                if (board.getSquare(i, y)->getColor() == color) {
                    break;
                }
                moves.push_back(Move(x, y, i, y));
                if (board.getSquare(i, y)->getColor() != Color::NONE) {
                    break;
                }
            }
            for (int i = x - 1; i >= 0; i--) {
                if (board.getSquare(i, y)->getColor() == color) {
                    break;
                }
                moves.push_back(Move(x, y, i, y));
                if (board.getSquare(i, y)->getColor() != Color::NONE) {
                    break;
                }
            }
            for (int i = y + 1; i < 8; i++) {
                if (board.getSquare(x, i)->getColor() == color) {
                    break;
                }
                moves.push_back(Move(x, y, x, i));
                if (board.getSquare(x, i)->getColor() != Color::NONE) {
                    break;
                }
            }
            for (int i = y - 1; i >= 0; i--) {
                if (board.getSquare(x, i)->getColor() == color) {
                    break;
                }
                moves.push_back(Move(x, y, x, i));
                if (board.getSquare(x, i)->getColor() != Color::NONE) {
                    break;
                }
            }

            return moves;
        };

        std::vector<Move> getQueenMoves(Board& board, int x, int y) {
            // use the above functions
            std::vector<Move> moves;
            std::vector<Move> diagonalMoves = getDiagonalMoves(board, x, y);
            std::vector<Move> straightMoves = getStraightMoves(board, x, y);
            moves.insert(moves.end(), diagonalMoves.begin(), diagonalMoves.end());
            moves.insert(moves.end(), straightMoves.begin(), straightMoves.end());
            return moves;
        };

        std::vector<Move> getBishopMoves(Board& board, int x, int y) {
            std::vector<Move> moves;
            std::vector<Move> diagonalMoves = getDiagonalMoves(board, x, y);
            moves.insert(moves.end(), diagonalMoves.begin(), diagonalMoves.end());
            return moves;
        };

        std::vector<Move> getRookMoves(Board& board, int x, int y) {
            std::vector<Move> moves;
            std::vector<Move> straightMoves = getStraightMoves(board, x, y);
            moves.insert(moves.end(), straightMoves.begin(), straightMoves.end());
            return moves;
        };

        std::vector<Move> getKnightMoves(Board& board, int x, int y) {
            std::vector<Move> moves;
            Color color = board.getSquare(x, y)->getColor();
            if (x > 1) {
                if (y > 0) {
                    if (board.getSquare(x - 2, y - 1)->getColor() != color) {
                        moves.push_back(Move(x, y, x - 2, y - 1));
                    }
                }
                if (y < 7) {
                    if (board.getSquare(x - 2, y + 1)->getColor() != color) {
                        moves.push_back(Move(x, y, x - 2, y + 1));
                    }
                }
            }
            if (x < 6) {
                if (y > 0) {
                    if (board.getSquare(x + 2, y - 1)->getColor() != color) {
                        moves.push_back(Move(x, y, x + 2, y - 1));
                    }
                }
                if (y < 7) {
                    if (board.getSquare(x + 2, y + 1)->getColor() != color) {
                        moves.push_back(Move(x, y, x + 2, y + 1));
                    }
                }
            }
            if (y > 1) {
                if (x > 0) {
                    if (board.getSquare(x - 1, y - 2)->getColor() != color) {
                        moves.push_back(Move(x, y, x - 1, y - 2));
                    }
                }
                if (x < 7) {
                    if (board.getSquare(x + 1, y - 2)->getColor() != color) {
                        moves.push_back(Move(x, y, x + 1, y - 2));
                    }
                }
            }
            if (y < 6) {
                if (x > 0) {
                    if (board.getSquare(x - 1, y + 2)->getColor() != color) {
                        moves.push_back(Move(x, y, x - 1, y + 2));
                    }
                }
                if (x < 7) {
                    if (board.getSquare(x + 1, y + 2)->getColor() != color) {
                        moves.push_back(Move(x, y, x + 1, y + 2));
                    }
                }
            }
            return moves;
        };

        std::vector<Move> getKingMoves(Board& board, int x, int y) {
            std::vector<Move> moves;
            Color color = board.getSquare(x, y)->getColor();
            // like queen but only one square
            if (x > 0) {
                if (y > 0) {
                    if (board.getSquare(x - 1, y - 1)->getColor() != color) {
                        moves.push_back(Move(x, y, x - 1, y - 1));
                    }
                }
                if (board.getSquare(x - 1, y)->getColor() != color) {
                    moves.push_back(Move(x, y, x - 1, y));
                }
                if (y < 7) {
                    if (board.getSquare(x - 1, y + 1)->getColor() != color) {
                        moves.push_back(Move(x, y, x - 1, y + 1));
                    }
                }
            }
            if (x < 7) {
                if (y > 0) {
                    if (board.getSquare(x + 1, y - 1)->getColor() != color) {
                        moves.push_back(Move(x, y, x + 1, y - 1));
                    }
                }
                if (board.getSquare(x + 1, y)->getColor() != color) {
                    moves.push_back(Move(x, y, x + 1, y));
                }
                if (y < 7) {
                    if (board.getSquare(x + 1, y + 1)->getColor() != color) {
                        moves.push_back(Move(x, y, x + 1, y + 1));
                    }
                }
            }
            if (y > 0) {
                if (board.getSquare(x, y - 1)->getColor() != color) {
                    moves.push_back(Move(x, y, x, y - 1));
                }
            }
            if (y < 7) {
                if (board.getSquare(x, y + 1)->getColor() != color) {
                    moves.push_back(Move(x, y, x, y + 1));
                }
            }
            return moves;
        };

        std::vector<Move> getPawnMoves(Board& board, int x, int y) {
            std::vector<Move> moves;
            Color color = board.getSquare(x, y)->getColor();
            // including en passant from lastmove
            if (color == Color::WHITE) {
                if (y == 1) {
                    if (board.getSquare(x, y + 1)->getColor() == Color::NONE && board.getSquare(x, y + 2)->getColor() == Color::NONE) {
                        moves.push_back(Move(x, y, x, y + 2));
                    }
                }
                if (board.getSquare(x, y + 1)->getColor() == Color::NONE) {
                    moves.push_back(Move(x, y, x, y + 1));
                }
                if (x > 0) {
                    if (board.getSquare(x - 1, y + 1)->getColor() == Color::BLACK) {
                        moves.push_back(Move(x, y, x - 1, y + 1));
                    }
                }
                if (x < 7) {
                    if (board.getSquare(x + 1, y + 1)->getColor() == Color::BLACK) {
                        moves.push_back(Move(x, y, x + 1, y + 1));
                    }
                }
                if (board.getLastMove().getX2() == x - 1 && board.getLastMove().getY2() == y && board.getLastMove().getY1() == y + 2) {
                    moves.push_back(Move(x, y, x - 1, y + 1, true));
                }
                if (board.getLastMove().getX2() == x + 1 && board.getLastMove().getY2() == y && board.getLastMove().getY1() == y + 2) {
                    moves.push_back(Move(x, y, x + 1, y + 1, true));
                }
            } else {
                if (y == 6) {
                    if (board.getSquare(x, y - 1)->getColor() == Color::NONE && board.getSquare(x, y - 2)->getColor() == Color::NONE) {
                        moves.push_back(Move(x, y, x, y - 2));
                    }
                }
                if (board.getSquare(x, y - 1)->getColor() == Color::NONE) {
                    moves.push_back(Move(x, y, x, y - 1));
                }
                if (x > 0) {
                    if (board.getSquare(x - 1, y - 1)->getColor() == Color::WHITE) {
                        moves.push_back(Move(x, y, x - 1, y - 1));
                    }
                }
                if (x < 7) {
                    if (board.getSquare(x + 1, y - 1)->getColor() == Color::WHITE) {
                        moves.push_back(Move(x, y, x + 1, y - 1));
                    }
                }
                if (board.getLastMove().getX2() == x - 1 && board.getLastMove().getY2() == y && board.getLastMove().getY1() == y - 2) {
                    moves.push_back(Move(x, y, x - 1, y - 1, true));
                }
                if (board.getLastMove().getX2() == x + 1 && board.getLastMove().getY2() == y && board.getLastMove().getY1() == y - 2) {
                    moves.push_back(Move(x, y, x + 1, y - 1, true));
                }
            }
            return moves;
        };

        std::vector<Move> getPseudoLegalMoves(Board& board, int x, int y) {
            std::vector<Move> moves = {};
            Square* square = board.getSquare(x, y);
            if (square->getColor() == board.getTurn()) {
                switch (square->getPiece()) {
                    case Piece::PAWN:
                        return getPawnMoves(board, x, y);
                    case Piece::KNIGHT:
                        return getKnightMoves(board, x, y);
                    case Piece::BISHOP:
                        return getBishopMoves(board, x, y);
                    case Piece::ROOK:
                        return getRookMoves(board, x, y);
                    case Piece::QUEEN:
                        return getQueenMoves(board, x, y);
                    case Piece::KING:
                        return getKingMoves(board, x, y);
                    default:
                        return moves;
                }
            }
            return moves;
        };

        std::vector<Move> getPseudoLegalMoves(Board& board) {
            std::vector<Move> moves = {};
            for (int i = 0; i < 64; i++) {
                int x = i % 8;
                int y = i / 8;
                std::vector<Move> squareMoves = getPseudoLegalMoves(board, x, y);
                moves.insert(moves.end(), squareMoves.begin(), squareMoves.end());
            }
            return moves;
        };

        // note! it is assumed that getPseudoLegalMoves has been called before this
        bool isWhiteCheck(Board& board) {
            Square* kingSquare = board.getWhiteKingSquare();
            std::vector<Move> moves = getPseudoLegalMoves(board);
            for (int i = 0; i < moves.size(); i++) {
                // if kind is moving
                if (moves[i].getX2() == kingSquare->getX() && moves[i].getY2() == kingSquare->getY()) {
                    return true;
                }
            }

            return false;
        };

        // note! it is assumed that getPseudoLegalMoves has been called before this
        bool isBlackCheck(Board& board) {
            Square* kingSquare = board.getBlackKingSquare();
            std::vector<Move> moves = getPseudoLegalMoves(board);
            for (int i = 0; i < moves.size(); i++) {
                // if kind is moving
                if (moves[i].getX2() == kingSquare->getX() && moves[i].getY2() == kingSquare->getY()) {
                    return true;
                }
            }

            return false;
        };

        std::vector<Move> getLegalMoves(Board& board) {
            std::vector<Move> moves = getPseudoLegalMoves(board);
            std::vector<Move> legalMoves = {};
            for (int i = 0; i < moves.size(); i++) {
                Board newBoard;
                newBoard.setPos(board.getSquares());
                newBoard.setTurn(board.getTurn());
                newBoard.setBlackKingSquare(board.getBlackKingSquare());
                newBoard.setWhiteKingSquare(board.getWhiteKingSquare());
                newBoard.move(moves[i]);
                if (board.getTurn() == Color::WHITE) {
                    if (!isWhiteCheck(newBoard)) {
                        legalMoves.push_back(moves[i]);
                    }
                } else {
                    if (!isBlackCheck(newBoard)) {
                        legalMoves.push_back(moves[i]);
                    }
                }
            }
            return legalMoves;
        };

        bool isEnd(Board& board) {
            return getLegalMoves(board).size() == 0;
        };
    }
}