#pragma once

#include <chess/include.h>
#include <display.h>
#include <palette.h>
#include "piecesui.h"

namespace ChessUI {
    void drawPiece(Chess::Piece piece, Chess::Color color, int x, int y) {
        switch (piece) {
            case Chess::Piece::PAWN:
                drawPawn(color, x, y);
                break;
            case Chess::Piece::KNIGHT:
                drawKnight(color, x, y);
                break;
            case Chess::Piece::BISHOP:
                drawBishop(color, x, y);
                break;
            case Chess::Piece::ROOK:
                drawRook(color, x, y);
                break;
            case Chess::Piece::QUEEN:
                drawQueen(color, x, y);
                break;
            case Chess::Piece::KING:
                drawKing(color, x, y);
                break;
            default:
                break;
        }
    }

    void drawBoard(Chess::Board& board) {
        for (int i = 0; i < 64; i++) {
            Chess::Square* square = board.getSquare(i);
            int x = i % 8;
            int y = i / 8;
            EADK::Rect rect = {x * 30, y * 30, 30, 30};
            EADK::Display::pushRectUniform(rect, (x + y) % 2 == 0 ? EADK::Color(0xEEEEEE) : EADK::Color(0xAAAAAA));
            if (square->getPiece() != Chess::Piece::EMPTY) {
                drawPiece(square->getPiece(), square->getColor(), x, y);
            }
        }
    }
}