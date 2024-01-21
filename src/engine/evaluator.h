#pragma once

#include <chess/include.h>
#include <pqtables.h>

namespace Evaluator {
    int getPieceValue(Chess::Piece piece, Chess::Color color) {
        int value = 0;
        switch (piece) {
            case Chess::Piece::PAWN:
                value = 10;
                break;
            case Chess::Piece::KNIGHT:
                value = 30;
                break;
            case Chess::Piece::BISHOP:
                value = 33;
                break;
            case Chess::Piece::ROOK:
                value = 50;
                break;
            case Chess::Piece::QUEEN:
                value = 90;
                break;
            case Chess::Piece::KING:
                value = 900;
            default:
                value = 0;
                break;
        }

        return color == Chess::Color::WHITE ? value : -value;
    }

    int applyPQTable(int value, int index, Chess::Piece piece, Chess::Color color) {
        switch (color) {
            case Chess::Color::WHITE:
                switch (piece) {
                    case Chess::Piece::PAWN:
                        return value + PQTables::White::PAWN[index];
                    case Chess::Piece::KNIGHT:
                        return value + PQTables::White::KNIGHT[index];
                    case Chess::Piece::BISHOP:
                        return value + PQTables::White::BISHOP[index];
                    case Chess::Piece::ROOK:
                        return value + PQTables::White::ROOK[index];
                    case Chess::Piece::QUEEN:
                        return value + PQTables::White::QUEEN[index];
                    case Chess::Piece::KING:
                        return value + PQTables::White::KING[index];
                    default:
                        return value;
                }
            case Chess::Color::BLACK:
                switch (piece) {
                    case Chess::Piece::PAWN:
                        return value + PQTables::Black::PAWN[index];
                    case Chess::Piece::KNIGHT:
                        return value + PQTables::Black::KNIGHT[index];
                    case Chess::Piece::BISHOP:
                        return value + PQTables::Black::BISHOP[index];
                    case Chess::Piece::ROOK:
                        return value + PQTables::Black::ROOK[index];
                    case Chess::Piece::QUEEN:
                        return value + PQTables::Black::QUEEN[index];
                    case Chess::Piece::KING:
                        return value + PQTables::Black::KING[index];
                    default:
                        return value;
                }
            default:
                return value;
        }
    }

    int evaluateMaterial(Chess::Board& board) {
        int score = 0;
        for (int i = 0; i < 64; i++) {
            Chess::Piece piece = board.getSquare(i)->getPiece();
            if (piece == Chess::Piece::EMPTY) continue;
            score += applyPQTable(getPieceValue(piece, board.getSquare(i)->getColor()), i, piece, board.getSquare(i)->getColor());
        }
        return score;
    }

    int evaluate(Chess::Board& board) {
        int score = 0;
        score += evaluateMaterial(board);
        return board.getTurn() == Chess::Color::WHITE ? score : -score;
    }

    int minmax(Chess::Board& board, int depth, int alpha, int beta) {
        if (depth == 0) return evaluate(board);
        std::vector<Chess::Move> moves = Chess::Generator::getLegalMoves(board);
        int bestScore = -9999;
        for (Chess::Move move : moves) {
            board.move(move);
            int score = -minmax(board, depth - 1, -beta, -alpha);
            board.undo();
            if (score > bestScore) bestScore = score;
            if (score > alpha) alpha = score;
            if (alpha >= beta) break;
        }
        return bestScore;
    }

    Chess::Move getBestMove(Chess::Board& board) {
        std::vector<Chess::Move> moves = Chess::Generator::getLegalMoves(board);
        Chess::Move bestMove = moves[0];
        Chess::Board boardCopy = Chess::Board::copyBoard(board);
        int bestScore = -9999;
        for (Chess::Move move : moves) {
            boardCopy.move(move);
            int score = -minmax(boardCopy, 2, -9999, 9999);
            boardCopy.undo();
            if (score > bestScore) {
                bestScore = score;
                bestMove = move;
            }
        }

        return bestMove;
    }
}