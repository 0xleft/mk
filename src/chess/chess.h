#pragma once

#include <cmath>
#include <vector>
#include <display.h>
#include <eadkpp.h>

namespace Chess {
    enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
    enum Color { WHITE, BLACK, NONE };

    class Square {
    private:
        Piece piece = EMPTY;
        Color color = NONE;
        bool moved = false;
        int x, y;
    public:
        void setSpace(Square* piece) { this->piece = piece->getPiece(); this->color = piece->getColor(); };
        void setEmpty() {
            this->piece = EMPTY;
            this->color = NONE;
        }
        void setPieceAndColor(Piece, Color) {
            this->piece = piece;
            this->color = color;
        }
        Piece getPiece() { return this->piece; }
        Color getColor() { return this->color; }
        void setX(int x) { this->x = x; }
        void setY(int y) { this->y = y; }
        void setMoved(bool moved) { this->moved = moved; }
        int getX() { return this->x; }
        int getY() { return this->y; }
        bool getMoved() { return this->moved; }
    };

    class Move {
    private:
        int x1, y1;
        int x2, y2;
        bool isCastle = false;
    public:
        Move(int x1, int y1, int x2, int y2) {
            this->x1 = x1; this->y1 = y1;
            this->x2 = x2; this->y2 = y2;
        }
        Move(int x1, int y1, int x2, int y2, bool isCastle) {
            this->x1 = x1; this->y1 = y1;
            this->x2 = x2; this->y2 = y2;
            this->isCastle = isCastle;
        }
        int getX1() { return this->x1; }
        int getY1() { return this->y1; }
        int getX2() { return this->x2; }
        int getY2() { return this->y2; }
        bool getIsCastle() { return this->isCastle; }

        void setX1(int x1) { this->x1 = x1; }
        void setY1(int y1) { this->y1 = y1; }
        void setX2(int x2) { this->x2 = x2; }
        void setY2(int y2) { this->y2 = y2; }
        void setIsCastle(bool isCastle) { this->isCastle = isCastle; }
    };

    class Board {
    private:
        Square square[8][8];
        Color turn = WHITE;
        // for en passant
        Move lastMove = Move(0, 0, 0, 0);

        std::vector<Move> getLegalMovesPawn(int x, int y);
        std::vector<Move> getLegalMovesRook(int x, int y);
        std::vector<Move> getLegalMovesKnight(int x, int y);
        std::vector<Move> getLegalMovesBishop(int x, int y);
        std::vector<Move> getLegalMovesQueen(int x, int y);
        std::vector<Move> getLegalMovesKing(int x, int y);
    public:
        Square* getSquare(int x, int y) {
            return &square[x][y];
        }
        void setSquare(Square& square, int x, int y){
            this->square[x][y] = square;
        }

        Board() {
            for (int i = 0; i < 8; i++) {
                square[i][1].setPieceAndColor(PAWN, WHITE);
                square[i][6].setPieceAndColor(PAWN, BLACK);
            }
            square[0][0].setPieceAndColor(ROOK, WHITE);
            square[1][0].setPieceAndColor(KNIGHT, WHITE);
            square[2][0].setPieceAndColor(BISHOP, WHITE);
            square[3][0].setPieceAndColor(QUEEN, WHITE);
            square[4][0].setPieceAndColor(KING, WHITE);
            square[5][0].setPieceAndColor(BISHOP, WHITE);
            square[6][0].setPieceAndColor(KNIGHT, WHITE);
            square[7][0].setPieceAndColor(ROOK, WHITE);

            square[0][7].setPieceAndColor(ROOK, BLACK);
            square[1][7].setPieceAndColor(KNIGHT, BLACK);
            square[2][7].setPieceAndColor(BISHOP, BLACK);
            square[3][7].setPieceAndColor(QUEEN, BLACK);
            square[4][7].setPieceAndColor(KING, BLACK);
            square[5][7].setPieceAndColor(BISHOP, BLACK);
            square[6][7].setPieceAndColor(KNIGHT, BLACK);
            square[7][7].setPieceAndColor(ROOK, BLACK);
        }

        void move(Move move) {
            Square* square1 = getSquare(move.getX1(), move.getY1());
            Square* square2 = getSquare(move.getX2(), move.getY2());
            square2->setSpace(square1);
            square1->setEmpty();
            square2->setMoved(true);
            lastMove = move;
            if (turn == WHITE) {
                turn = BLACK;
            }
            else {
                turn = WHITE;
            }
        }

        std::vector<Square*> getPieces(Color color) {
            std::vector<Square*> pieces;
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    Square* square = getSquare(x, y);
                    if (square->getColor() == color) {
                        pieces.push_back(square);
                    }
                }
            }
            return pieces;
        }

        std::vector<Square*> getAllPieces() {
            std::vector<Square*> pieces;
            for (int x = 0; x < 8; x++) {
                for (int y = 0; y < 8; y++) {
                    Square* square = getSquare(x, y);
                    if (square->getColor() != NONE) {
                        pieces.push_back(square);
                    }
                }
            }
            return pieces;
        }

        Color getTurn() { return this->turn; }
        void setTurn(Color turn) { this->turn = turn; }
        Move getLastMove() { return this->lastMove; }
        void setLastMove(Move lastMove) { this->lastMove = lastMove; }

        // legal moves
        std::vector<Move> getLegalMoves();
        void draw();
    };
}