#pragma once

#include "chess.h"

namespace Chess {
    class Generator {
    private:
        static std::vector<Move> getPawnMoves(Board& board, int x, int y);
        static std::vector<Move> getKingMoves(Board& board, int x, int y);
        static std::vector<Move> getKnightMoves(Board& board, int x, int y);
        static std::vector<Move> getQueenMoves(Board& board, int x, int y);
        static std::vector<Move> getRookMoves(Board& board, int x, int y);
        static std::vector<Move> getBishopMoves(Board& board, int x, int y);
        static std::vector<Move> getStraightMoves(Board& board, int x, int y);
        static std::vector<Move> getDiagonalMoves(Board& board, int x, int y);
    public:
        static std::vector<Move> getPseudoLegalMoves(Board& board);
        static std::vector<Move> getLegalMoves(Board& board);
        static std::vector<Move> getPseudoLegalMoves(Board& board, int x, int y);
    };
}

namespace Chess {
}