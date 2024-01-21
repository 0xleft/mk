#pragma once

#include <cstdint>
#include <cassert>

#include "color.hpp"

namespace chess {

class PieceType {
   public:
    enum class underlying : std::uint8_t {
        PAWN,
        KNIGHT,
        BISHOP,
        ROOK,
        QUEEN,
        KING,
        NONE,
    };

    PieceType() : pt(underlying::NONE) {}
    PieceType(underlying pt) : pt(pt) {}
    explicit PieceType(bpstd::string_view type) : pt(underlying::NONE) {
        switch (type.data()[0]) {
            case 'P':
                pt = underlying::PAWN;
                break;
            case 'N':
                pt = underlying::KNIGHT;
                break;
            case 'B':
                pt = underlying::BISHOP;
                break;
            case 'R':
                pt = underlying::ROOK;
                break;
            case 'Q':
                pt = underlying::QUEEN;
                break;
            case 'K':
                pt = underlying::KING;
                break;

            case 'p':
                pt = underlying::PAWN;
                break;
            case 'n':
                pt = underlying::KNIGHT;
                break;
            case 'b':
                pt = underlying::BISHOP;
                break;
            case 'r':
                pt = underlying::ROOK;
                break;
            case 'q':
                pt = underlying::QUEEN;
                break;
            case 'k':
                pt = underlying::KING;
                break;
            default:
                pt = underlying::NONE;
                break;
        }
    }

    explicit operator std::string() const {
        switch (pt) {
            case underlying::PAWN:
                return "p";
            case underlying::KNIGHT:
                return "n";
            case underlying::BISHOP:
                return "b";
            case underlying::ROOK:
                return "r";
            case underlying::QUEEN:
                return "q";
            case underlying::KING:
                return "k";
            default:
                return " ";
        }
    }

    bool operator==(const PieceType& rhs) const noexcept { return pt == rhs.pt; }
    bool operator!=(const PieceType& rhs) const noexcept { return pt != rhs.pt; }

    operator int() const noexcept { return static_cast<int>(pt); }

    [[nodiscard]] underlying internal() const noexcept { return pt; }

    const static underlying PAWN   = underlying::PAWN;
    const static underlying KNIGHT = underlying::KNIGHT;
    const static underlying BISHOP = underlying::BISHOP;
    const static underlying ROOK   = underlying::ROOK;
    const static underlying QUEEN  = underlying::QUEEN;
    const static underlying KING   = underlying::KING;
    const static underlying NONE   = underlying::NONE;

   private:
    underlying pt;
};

inline std::ostream& operator<<(std::ostream& os, const PieceType& pt) {
    os << static_cast<std::string>(pt);
    return os;
}

class Piece {
   public:
    enum class underlying : std::uint8_t {
        WHITEPAWN,
        WHITEKNIGHT,
        WHITEBISHOP,
        WHITEROOK,
        WHITEQUEEN,
        WHITEKING,
        BLACKPAWN,
        BLACKKNIGHT,
        BLACKBISHOP,
        BLACKROOK,
        BLACKQUEEN,
        BLACKKING,
        NONE
    };

    Piece() : piece(underlying::NONE) {}
    Piece(underlying piece) : piece(piece) {}
    Piece(PieceType type, Color color)
        : piece(color == Color::NONE      ? Piece::NONE
                : type == PieceType::NONE ? Piece::NONE
                                          : static_cast<underlying>(static_cast<int>(color.internal()) * 6 + type)) {}
    Piece(Color color, PieceType type)
        : piece(color == Color::NONE      ? Piece::NONE
                : type == PieceType::NONE ? Piece::NONE
                                          : static_cast<underlying>(static_cast<int>(color.internal()) * 6 + type)) {}
    Piece(bpstd::string_view p) : piece(underlying::NONE) {
        switch (p.data()[0]) {
            case 'P':
                piece = WHITEPAWN;
                break;
            case 'N':
                piece = WHITEKNIGHT;
                break;
            case 'B':
                piece = WHITEBISHOP;
                break;
            case 'R':
                piece = WHITEROOK;
                break;
            case 'Q':
                piece = WHITEQUEEN;
                break;
            case 'K':
                piece = WHITEKING;
                break;
            // black
            case 'p':
                piece = BLACKPAWN;
                break;
            case 'n':
                piece = BLACKKNIGHT;
                break;
            case 'b':
                piece = BLACKBISHOP;
                break;
            case 'r':
                piece = BLACKROOK;
                break;
            case 'q':
                piece = BLACKQUEEN;
                break;
            case 'k':
                piece = BLACKKING;
                break;
            default:
                piece = NONE;
                break;
        }
    }

    bool operator<(const Piece& rhs) const noexcept { return piece < rhs.piece; }
    bool operator>(const Piece& rhs) const noexcept { return piece > rhs.piece; }
    bool operator==(const Piece& rhs) const noexcept { return piece == rhs.piece; }
    bool operator!=(const Piece& rhs) const noexcept { return piece != rhs.piece; }

    bool operator==(const underlying& rhs) const noexcept { return piece == rhs; }
    bool operator!=(const underlying& rhs) const noexcept { return piece != rhs; }

    bool operator==(const PieceType& rhs) const noexcept { return type() == rhs; }
    bool operator!=(const PieceType& rhs) const noexcept { return type() != rhs; }

    explicit operator std::string() const {
        switch (piece) {
            case WHITEPAWN:
                return "P";
            case WHITEKNIGHT:
                return "N";
            case WHITEBISHOP:
                return "B";
            case WHITEROOK:
                return "R";
            case WHITEQUEEN:
                return "Q";
            case WHITEKING:
                return "K";
            // black
            case BLACKPAWN:
                return "p";
            case BLACKKNIGHT:
                return "n";
            case BLACKBISHOP:
                return "b";
            case BLACKROOK:
                return "r";
            case BLACKQUEEN:
                return "q";
            case BLACKKING:
                return "k";
            default:
                return ".";
        }
    }

    operator int() const noexcept { return static_cast<int>(piece); }

    [[nodiscard]] PieceType type() const noexcept {
        return static_cast<PieceType::underlying>(int(piece) % 6);
    }

    [[nodiscard]] Color color() const noexcept {
        if (piece == NONE) {
            return Color::NONE;
        }
        return static_cast<Color>(static_cast<int>(piece) / 6);
    }

    [[nodiscard]] underlying internal() const noexcept { return piece; }

    const static underlying NONE        = underlying::NONE;
    const static underlying WHITEPAWN   = underlying::WHITEPAWN;
    const static underlying WHITEKNIGHT = underlying::WHITEKNIGHT;
    const static underlying WHITEBISHOP = underlying::WHITEBISHOP;
    const static underlying WHITEROOK   = underlying::WHITEROOK;
    const static underlying WHITEQUEEN  = underlying::WHITEQUEEN;
    const static underlying WHITEKING   = underlying::WHITEKING;
    const static underlying BLACKPAWN   = underlying::BLACKPAWN;
    const static underlying BLACKKNIGHT = underlying::BLACKKNIGHT;
    const static underlying BLACKBISHOP = underlying::BLACKBISHOP;
    const static underlying BLACKROOK   = underlying::BLACKROOK;
    const static underlying BLACKQUEEN  = underlying::BLACKQUEEN;
    const static underlying BLACKKING   = underlying::BLACKKING;

   private:
    underlying piece;
};
}  // namespace chess
