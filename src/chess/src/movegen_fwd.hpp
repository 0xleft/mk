#pragma once

namespace chess {
    namespace movegen {
        enum MoveGenType {
            ALL,
            CAPTURE,
            QUIET
        };
    }
}

#include <cstdint>

#include "movelist.hpp"



namespace chess {
enum PieceGenType {
    PAWN   = 1,
    KNIGHT = 2,
    BISHOP = 4,
    ROOK   = 8,
    QUEEN  = 16,
    KING   = 32,
};


class Board;

namespace movegen {
    template <chess::movegen::MoveGenType mt = chess::movegen::MoveGenType::ALL>
    void static legalmoves(Movelist &movelist, const Board &board,
                           int pieces = PieceGenType::PAWN | PieceGenType::KNIGHT | PieceGenType::BISHOP |
                                        PieceGenType::ROOK | PieceGenType::QUEEN | PieceGenType::KING);

    static std::array<std::array<Bitboard, 64>, 64> init_squares_between();

    /// @brief Generate the checkmask.
    /// Returns a bitboard where the attacker path between the king and enemy piece is set.
    /// @tparam c
    /// @param board
    /// @param sq
    /// @param double_check
    /// @return
    template <Color::underlying c>
    static Bitboard checkMask(const Board &board, Square sq, int &double_check);

    /// @brief Generate the pin mask for horizontal and vertical pins.
    /// Returns a bitboard where the ray between the king and the pinner is set.
    /// @tparam c
    /// @param board
    /// @param sq
    /// @param occ_enemy
    /// @param occ_us
    /// @return
    template <Color::underlying c>
    static Bitboard pinMaskRooks(const Board &board, Square sq, Bitboard occ_enemy, Bitboard occ_us);

    /// @brief Generate the pin mask for diagonal pins.
    /// Returns a bitboard where the ray between the king and the pinner is set.
    /// @tparam c
    /// @param board
    /// @param sq
    /// @param occ_enemy
    /// @param occ_us
    /// @return
    template <Color::underlying c>
    static Bitboard pinMaskBishops(const Board &board, Square sq, Bitboard occ_enemy, Bitboard occ_us);

    /// @brief Returns the squares that are attacked by the enemy
    /// @tparam c
    /// @param board
    /// @param enemy_empty
    /// @return
    template <Color::underlying c>
    static Bitboard seenSquares(const Board &board, Bitboard enemy_empty);

    /// @brief Generate pawn moves.
    /// @tparam c
    /// @tparam mt
    /// @param board
    /// @param moves
    /// @param pin_d
    /// @param pin_hv
    /// @param checkmask
    /// @param occ_enemy
    template <Color::underlying c, chess::movegen::MoveGenType mt>
    static void generatePawnMoves(const Board &board, Movelist &moves, Bitboard pin_d, Bitboard pin_hv,
                                  Bitboard checkmask, Bitboard occ_enemy);

    /// @brief Generate knight moves.
    /// @param sq
    /// @param movable
    /// @return
    static Bitboard generateKnightMoves(Square sq);

    /// @brief Generate bishop moves.
    /// @param sq
    /// @param movable
    /// @param pin_d
    /// @param occ_all
    /// @return
    static Bitboard generateBishopMoves(Square sq, Bitboard pin_d, Bitboard occ_all);

    /// @brief Generate rook moves.
    /// @param sq
    /// @param movable
    /// @param pin_hv
    /// @param occ_all
    /// @return
    static Bitboard generateRookMoves(Square sq, Bitboard pin_hv, Bitboard occ_all);

    /// @brief Generate queen moves.
    /// @param sq
    /// @param movable
    /// @param pin_d
    /// @param pin_hv
    /// @param occ_all
    /// @return
    static Bitboard generateQueenMoves(Square sq, Bitboard pin_d, Bitboard pin_hv, Bitboard occ_all);
    /// @brief Generate king moves.
    /// @param sq
    /// @param seen
    /// @param movable_square
    /// @return
    static Bitboard generateKingMoves(Square sq, Bitboard seen, Bitboard movable_square);

    /// @brief Generate castling moves.
    /// @tparam c
    /// @tparam mt
    /// @param board
    /// @param sq
    /// @param seen
    /// @param pinHV
    /// @return
    template <Color::underlying c, chess::movegen::MoveGenType mt>
    static Bitboard generateCastleMoves(const Board &board, Square sq, Bitboard seen, Bitboard pinHV);

    template <typename T>
    static void whileBitboardAdd(Movelist &movelist, Bitboard mask, std::function<T> func);

    /// @brief all legal moves for a position
    /// @tparam c
    /// @tparam mt
    /// @param movelist
    /// @param board
    template <Color::underlying c, chess::movegen::MoveGenType mt>
    static void legalmoves(Movelist &movelist, const Board &board, int pieces);
};

}