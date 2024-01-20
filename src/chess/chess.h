#pragma once

#include <cmath>
#include <vector>
#include <display.h>
#include <eadkpp.h>
#include <str.h>

#ifdef CHESS_DEBUG
#include <iostream>
#include <string>
#endif

// todo split up into different files

namespace Chess {
    enum Piece { KING, QUEEN, BISHOP, KNIGHT, ROOK, PAWN, EMPTY };
    enum Color { WHITE, BLACK, NONE };

    class Utils {
        public:
        static Piece getPiece(char c) {
            c = tolower(c);
            switch (c) {
            case 'k':
                return KING;
            case 'q':
                return QUEEN;
            case 'b':
                return BISHOP;
            case 'n':
                return KNIGHT;
            case 'r':
                return ROOK;
            case 'p':
                return PAWN;
            default:
                return EMPTY;
            }
        };

        static Color getColor(char c) {
            if (c >= 'A' && c <= 'Z') {
                return WHITE;
            }
            else {
                return BLACK;
            }
        };

        static char getPieceChar(Piece piece, Color color) {
            char c;
            switch (piece) {
            case KING:
                c = 'K';
                break;
            case QUEEN:
                c = 'Q';
                break;
            case BISHOP:
                c = 'B';
                break;
            case KNIGHT:
                c = 'N';
                break;
            case ROOK:
                c = 'R';
                break;
            case PAWN:
                c = 'P';
                break;
            default:
                c = ' ';
                break;
            }

            if (color == BLACK) {
                c = tolower(c);
            }
            return c;
        };

        static char getColorChar(Color color) {
            if (color == WHITE) {
                return 'w';
            }
            else {
                return 'b';
            }
        };
    };
    
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
        bool isEmpty() { return this->piece == EMPTY; }
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
        bool isCapture = false;
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
        bool getIsCapture() { return this->isCapture; }

        void setX1(int x1) { this->x1 = x1; }
        void setY1(int y1) { this->y1 = y1; }
        void setX2(int x2) { this->x2 = x2; }
        void setY2(int y2) { this->y2 = y2; }
        void setIsCastle(bool isCastle) { this->isCastle = isCastle; }
        void setIsCapture(bool isCapture) { this->isCapture = isCapture; }
#ifdef CHESS_DEBUG
        std::string UCI() {
            std::string uci = "";
            uci += (char)(x1 + 'a');
            uci += (char)(y1 + '1');
            uci += (char)(x2 + 'a');
            uci += (char)(y2 + '1');
            return uci;
        }
#endif
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
            return this->squares[x + y * 8];
        }

        std::vector<Square*> getSquares() {
            return this->squares;
        }
        void setPos(std::vector<Square*> squares) {
            for (int i = 0; i < 64; i++) {
                this->squares[i]->setPieceAndColor(squares[i]->getPiece(), squares[i]->getColor());
            }
        }

        void setBlackKingSquare(Square* square) { this->blackKingSquare = square; }
        void setWhiteKingSquare(Square* square) { this->whiteKingSquare = square; }

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
            square2->setPieceAndColor(square1->getPiece(), square1->getColor());
            square1->setEmpty();
            square2->setMoved(true);
            // en passant
            if (square1->getPiece() == PAWN && abs(move.getY2() - move.getY1()) == 2) {
                this->lastMove = move;
            }
            else {
                this->lastMove = Move(0, 0, 0, 0);
            }
            // remove en passant pawn
            if (move.getIsCapture() && square2->getPiece() == PAWN && this->lastMove.getX2() == move.getX2() && this->lastMove.getY2() == move.getY2()) {
                if (square2->getColor() == WHITE) {
                    getSquare(move.getX2(), move.getY2() - 1)->setPieceAndColor(EMPTY, NONE);
                }
                else {
                    getSquare(move.getX2(), move.getY2() + 1)->setPieceAndColor(EMPTY, NONE);
                }
            }

            // castling
            if (move.getIsCastle()) {
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
            if (square2->getPiece() == PAWN && (square2->getY() == 0 || square2->getY() == 7)) {
                square2->setPieceAndColor(this->selectedPromotion, square2->getColor());
            }
            this->lastMove = move;
            if (turn == WHITE) {
                turn = BLACK;
            }
            else {
                turn = WHITE;
            }

            // update king square
            if (square2->getPiece() == KING) {
                if (square2->getColor() == WHITE) {
                    this->whiteKingSquare = square2;
                }
                else {
                    this->blackKingSquare = square2;
                }
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
        void setFen(std::string fen) {
            // std::cout << fen << std::endl; // rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R b KQkq - 1 2
            // clear board
            for (int i = 0; i < 8; i++) {
                for (int j = 0; j < 8 ; j++) {
                    this->getSquare(i, j)->setEmpty();
                }
            }

            // get piece part
            std::string piecePart = fen.substr(0, fen.find(" "));
            //std::cout << piecePart << std::endl; // rnbqkbnr/pp1ppppp/8/2p5/4P3/5N2/PPPP1PPP/RNBQKB1R
            int rank = 7;
            int file = 0;
            for (int i = 0; i < piecePart.length(); i++) {
                if (piecePart[i] == '/') {
                    rank--;
                    file = 0;
                } else if (piecePart[i] >= '1' && piecePart[i] <= '8') {
                    file += piecePart[i] - '0';
                } else {
                    this->getSquare(file, rank)->setPieceAndColor(Utils::getPiece(piecePart[i]), Utils::getColor(piecePart[i]));
                    file++;
                }
            }

            std::string turnPart = fen.substr(fen.find(" ") + 1, fen.find(" ", fen.find(" ") + 1) - fen.find(" ") - 1);
            // is this corrent? todo
            this->turn = turnPart == "w" ? WHITE : BLACK;
        }

        std::string getFen() {
            std::string fen = "";
            for (int i = 7; i >= 0; i--) {
                int empty = 0;
                for (int j = 0; j < 8; j++) {
                    if (this->getSquare(j, i)->isEmpty()) {
                        empty++;
                    } else {
                        if (empty != 0) {
                            fen += std::to_string(empty);
                            empty = 0;
                        }
                        fen += Utils::getPieceChar(this->getSquare(j, i)->getPiece(), this->getSquare(j, i)->getColor());
                    }
                }
                if (empty != 0) {
                    fen += std::to_string(empty);
                }
                if (i != 0) {
                    fen += "/";
                }
            }
            fen += " ";
            fen += Utils::getColorChar(this->turn);
            fen += " ";
            fen += "-";
            fen += " ";
            fen += "0";
            fen += " ";
            fen += "1";
            return fen;
        }

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