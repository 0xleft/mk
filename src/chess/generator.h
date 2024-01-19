#pragma once

#include "chess.h"

namespace Chess {
    class Generator {
    public:
        static std::vector<Move> getPseudoLegalMoves(Board& board);
        static std::vector<Move> getPseudoLegalMoves(Board& board, int x, int y);
    };
}

namespace Chess {
}