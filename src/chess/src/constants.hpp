#pragma once

#include "bitboard.hpp"

namespace chess::constants {

const Bitboard DEFAULT_CHECKMASK = Bitboard(0xFFFFFFFFFFFFFFFFull);
const auto STARTPOS              = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";
const auto MAX_MOVES             = 256;
}  // namespace chess::constants
