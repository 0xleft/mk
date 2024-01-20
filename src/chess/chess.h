#pragma once

#include <cmath>
#include <vector>
#include <display.h>
#include <eadkpp.h>

#ifdef CHESS_DEBUG
#include <iostream>
#endif

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
        Square(Piece piece, Color color) {
            this->piece = piece;
            this->color = color;
        }
        Square() {}
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
        Piece selectedPromotion = QUEEN;
        Square* blackKingSquare;
        Square* whiteKingSquare;
        // for en passant
        Move lastMove = Move(0, 0, 0, 0);
    public:
        Square* getSquare(int x, int y) {
            // if (x < 0 || x > 7 || y < 0 || y > 7) {
            //     return nullptr;
            // }
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

            blackKingSquare = getSquare(4, 7);
            whiteKingSquare = getSquare(4, 0);
        }

        void setSelectedPromotion(Piece piece) {
            this->selectedPromotion = piece;
        }
        Piece getSelectedPromotion() {
            return this->selectedPromotion;
        }

        Square* getBlackKingSquare() { return this->blackKingSquare; }
        Square* getWhiteKingSquare() { return this->whiteKingSquare; }

        void move(Move move) {
            Square* square1 = getSquare(move.getX1(), move.getY1());
            Square* square2 = getSquare(move.getX2(), move.getY2());
#ifdef CHESS_DEBUG
            if (square1->getPiece() == KING) {
                std::cout << "King moved" << std::endl;
                this->printBoard();
            }
#endif
            square2->setPieceAndColor(square1->getPiece(), square1->getColor());
            square1->setEmpty();
            square2->setMoved(true);
#ifdef CHESS_DEBUG
            if (square2->getPiece() == KING) {
                std::cout << "King moved" << std::endl;
                this->printBoard();
            }
#endif
            if (square1->getColor() == WHITE && square1->getPiece() == KING) {
                whiteKingSquare = square2;
            }
            else if (square1->getColor() == BLACK && square1->getPiece() == KING) {
                blackKingSquare = square2;
            }
            // en passant
            if (square1->getPiece() == PAWN && abs(move.getY2() - move.getY1()) == 2) {
                this->lastMove = move;
            }
            else {
                this->lastMove = Move(0, 0, 0, 0);
            }
            // castling
            if (square1->getPiece() == KING && abs(move.getX2() - move.getX1()) == 2) {
                if (move.getX2() == 2) {
                    getSquare(0, move.getY2())->setPieceAndColor(EMPTY, NONE);
                    getSquare(3, move.getY2())->setPieceAndColor(ROOK, square1->getColor());
                }
                else if (move.getX2() == 6) {
                    getSquare(7, move.getY2())->setPieceAndColor(EMPTY, NONE);
                    getSquare(5, move.getY2())->setPieceAndColor(ROOK, square1->getColor());
                }
            }
            // promotion
            if (square1->getPiece() == PAWN && (move.getY2() == 0 || move.getY2() == 7)) {
                square2->setPieceAndColor(selectedPromotion, square1->getColor());
            }
            this->lastMove = move;
            if (turn == WHITE) {
                turn = BLACK;
            }
            else {
                turn = WHITE;
            }
        }

        void undo() {
            Square* square1 = getSquare(lastMove.getX1(), lastMove.getY1());
            Square* square2 = getSquare(lastMove.getX2(), lastMove.getY2());
            square1->setPieceAndColor(square2->getPiece(), square2->getColor());
            square2->setEmpty();
            square1->setMoved(false);
            if (square2->getColor() == WHITE && square2->getPiece() == KING) {
                whiteKingSquare = square1;
            }
            else if (square2->getColor() == BLACK && square2->getPiece() == KING) {
                blackKingSquare = square1;
            }
            // en passant
            if (square2->getPiece() == PAWN && abs(lastMove.getY2() - lastMove.getY1()) == 2) {
                this->lastMove = Move(0, 0, 0, 0);
            }
            else {
                this->lastMove = Move(0, 0, 0, 0);
            }
            // castling
            if (square2->getPiece() == KING && abs(lastMove.getX2() - lastMove.getX1()) == 2) {
                if (lastMove.getX2() == 2) {
                    getSquare(0, lastMove.getY2())->setPieceAndColor(ROOK, square2->getColor());
                    getSquare(3, lastMove.getY2())->setPieceAndColor(EMPTY, NONE);
                }
                else if (lastMove.getX2() == 6) {
                    getSquare(7, lastMove.getY2())->setPieceAndColor(ROOK, square2->getColor());
                    getSquare(5, lastMove.getY2())->setPieceAndColor(EMPTY, NONE);
                }
            }
            // promotion
            if (square2->getPiece() == PAWN && (lastMove.getY2() == 0 || lastMove.getY2() == 7)) {
                square1->setPieceAndColor(PAWN, square2->getColor());
            }
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

#ifdef CHESS_DEBUG
        void printBoard() {
            for (int y = 7; y >= 0; y--) {
                for (int x = 0; x < 8; x++) {
                    Square* square = getSquare(x, y);
                    if (square->getPiece() == EMPTY) {
                        std::cout << "  ";
                    }
                    else {
                        if (square->getColor() == WHITE) {
                            std::cout << "w";
                        }
                        else {
                            std::cout << "b";
                        }
                        switch (square->getPiece()) {
                        case KING:
                            std::cout << "K";
                            break;
                        case QUEEN:
                            std::cout << "Q";
                            break;
                        case BISHOP:
                            std::cout << "B";
                            break;
                        case KNIGHT:
                            std::cout << "N";
                            break;
                        case ROOK:
                            std::cout << "R";
                            break;
                        case PAWN:
                            std::cout << "P";
                            break;
                        }
                    }
                    std::cout << " ";
                }
                std::cout << std::endl;
            }
        }
#endif
    };
}