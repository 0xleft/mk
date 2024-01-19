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
        void setEmpty() {
            this->piece = EMPTY;
            this->color = NONE;
        }
        void setPieceAndColor(Piece piece, Color color) {
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
        std::vector<Square*> squares;
        Color turn = WHITE;
        // for en passant
        Move lastMove = Move(0, 0, 0, 0);
    public:
        Square* getSquare(int x, int y) {
            return this->squares[x + y * 8];
        }

        Board() {
            for (int i = 0; i < 64; i++) {
                Square* square = new Square();
                square->setX(i % 8);
                square->setY(i / 8);
                squares.push_back(square);
            }

            for (int i = 0; i < 8; i++) {
                getSquare(i, 1)->setPieceAndColor(PAWN, WHITE);
                getSquare(i, 6)->setPieceAndColor(PAWN, BLACK);
            }

            getSquare(0, 0)->setPieceAndColor(ROOK, WHITE);
            getSquare(1, 0)->setPieceAndColor(KNIGHT, WHITE);
            getSquare(2, 0)->setPieceAndColor(BISHOP, WHITE);
            getSquare(3, 0)->setPieceAndColor(QUEEN, WHITE);
            getSquare(4, 0)->setPieceAndColor(KING, WHITE);
            getSquare(5, 0)->setPieceAndColor(BISHOP, WHITE);
            getSquare(6, 0)->setPieceAndColor(KNIGHT, WHITE);
            getSquare(7, 0)->setPieceAndColor(ROOK, WHITE);
            
            getSquare(0, 7)->setPieceAndColor(ROOK, BLACK);
            getSquare(1, 7)->setPieceAndColor(KNIGHT, BLACK);
            getSquare(2, 7)->setPieceAndColor(BISHOP, BLACK);
            getSquare(3, 7)->setPieceAndColor(QUEEN, BLACK);
            getSquare(4, 7)->setPieceAndColor(KING, BLACK);
            getSquare(5, 7)->setPieceAndColor(BISHOP, BLACK);
            getSquare(6, 7)->setPieceAndColor(KNIGHT, BLACK);
            getSquare(7, 7)->setPieceAndColor(ROOK, BLACK);
        }

        void move(Move move) {
            Square* square1 = getSquare(move.getX1(), move.getY1());
            Square* square2 = getSquare(move.getX2(), move.getY2());
            square2->setPieceAndColor(square1->getPiece(), square1->getColor());
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

        Color getTurn() { return this->turn; }
        void setTurn(Color turn) { this->turn = turn; }
        Move getLastMove() { return this->lastMove; }
        void setLastMove(Move lastMove) { this->lastMove = lastMove; }

        ~Board() {
            for (int i = 0; i < 64; i++) {
                delete squares[i];
            }
        }
    };
}