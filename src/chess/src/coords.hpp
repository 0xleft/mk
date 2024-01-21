#pragma once

#include <cstdint>
#include <string>
#include <string_view.hpp>
#include <cassert>

#include "color.hpp"

namespace chess {

class File {
   public:
    enum class underlying : std::uint8_t { FILE_A, FILE_B, FILE_C, FILE_D, FILE_E, FILE_F, FILE_G, FILE_H, NO_FILE };

    File() : file(underlying::NO_FILE) {}
    File(underlying file) : file(file) {}
    File(int file) : file(static_cast<underlying>(file)) {}

    underlying internal() const noexcept { return file; }

    bool operator==(const File& rhs) const noexcept { return file == rhs.file; }
    bool operator!=(const File& rhs) const noexcept { return file != rhs.file; }

    bool operator==(const underlying& rhs) const noexcept { return file == rhs; }
    bool operator!=(const underlying& rhs) const noexcept { return file != rhs; }

    bool operator>=(const File& rhs) const noexcept {
        return static_cast<int>(file) >= static_cast<int>(rhs.file);
    }
    bool operator<=(const File& rhs) const noexcept {
        return static_cast<int>(file) <= static_cast<int>(rhs.file);
    }

    bool operator>(const File& rhs) const noexcept {
        return static_cast<int>(file) > static_cast<int>(rhs.file);
    }
    bool operator<(const File& rhs) const noexcept {
        return static_cast<int>(file) < static_cast<int>(rhs.file);
    }

    operator int() const noexcept { return static_cast<int>(file); }

    explicit operator std::string() const { return std::string(1, static_cast<char>(static_cast<int>(file) + 'a')); }

    constexpr static underlying FILE_A  = underlying::FILE_A;
    constexpr static underlying FILE_B  = underlying::FILE_B;
    constexpr static underlying FILE_C  = underlying::FILE_C;
    constexpr static underlying FILE_D  = underlying::FILE_D;
    constexpr static underlying FILE_E  = underlying::FILE_E;
    constexpr static underlying FILE_F  = underlying::FILE_F;
    constexpr static underlying FILE_G  = underlying::FILE_G;
    constexpr static underlying FILE_H  = underlying::FILE_H;
    constexpr static underlying NO_FILE = underlying::NO_FILE;

   private:
    underlying file;
};

class Rank {
   public:
    enum class underlying { RANK_1, RANK_2, RANK_3, RANK_4, RANK_5, RANK_6, RANK_7, RANK_8, NO_RANK };

    Rank() : rank(underlying::NO_RANK) {}
    Rank(underlying rank) : rank(rank) {}
    Rank(int rank) : rank(static_cast<underlying>(rank)) {}

    underlying internal() const noexcept { return rank; }

    bool operator==(const Rank& rhs) const noexcept { return rank == rhs.rank; }
    bool operator!=(const Rank& rhs) const noexcept { return rank != rhs.rank; }

    bool operator==(const underlying& rhs) const noexcept { return rank == rhs; }
    bool operator!=(const underlying& rhs) const noexcept { return rank != rhs; }

    bool operator>=(const Rank& rhs) const noexcept {
        return static_cast<int>(rank) >= static_cast<int>(rhs.rank);
    }
    bool operator<=(const Rank& rhs) const noexcept {
        return static_cast<int>(rank) <= static_cast<int>(rhs.rank);
    }

    operator std::string() const { return std::string(1, static_cast<char>(static_cast<int>(rank) + '1')); }

    operator int() const noexcept { return static_cast<int>(rank); }

    static bool back_rank(Rank r, Color color) noexcept {
        if (color == Color::WHITE)
            return r == Rank::RANK_1;
        else
            return r == Rank::RANK_8;
    }

    constexpr static underlying RANK_1  = underlying::RANK_1;
    constexpr static underlying RANK_2  = underlying::RANK_2;
    constexpr static underlying RANK_3  = underlying::RANK_3;
    constexpr static underlying RANK_4  = underlying::RANK_4;
    constexpr static underlying RANK_5  = underlying::RANK_5;
    constexpr static underlying RANK_6  = underlying::RANK_6;
    constexpr static underlying RANK_7  = underlying::RANK_7;
    constexpr static underlying RANK_8  = underlying::RANK_8;
    constexpr static underlying NO_RANK = underlying::NO_RANK;

   private:
    underlying rank;
};

class Square {
   public:
    // clang-format off
    enum class underlying : uint8_t {
        SQ_A1, SQ_B1, SQ_C1, SQ_D1, SQ_E1, SQ_F1, SQ_G1, SQ_H1,
        SQ_A2, SQ_B2, SQ_C2, SQ_D2, SQ_E2, SQ_F2, SQ_G2, SQ_H2,
        SQ_A3, SQ_B3, SQ_C3, SQ_D3, SQ_E3, SQ_F3, SQ_G3, SQ_H3,
        SQ_A4, SQ_B4, SQ_C4, SQ_D4, SQ_E4, SQ_F4, SQ_G4, SQ_H4,
        SQ_A5, SQ_B5, SQ_C5, SQ_D5, SQ_E5, SQ_F5, SQ_G5, SQ_H5,
        SQ_A6, SQ_B6, SQ_C6, SQ_D6, SQ_E6, SQ_F6, SQ_G6, SQ_H6,
        SQ_A7, SQ_B7, SQ_C7, SQ_D7, SQ_E7, SQ_F7, SQ_G7, SQ_H7,
        SQ_A8, SQ_B8, SQ_C8, SQ_D8, SQ_E8, SQ_F8, SQ_G8, SQ_H8,
        NO_SQ
    };
    // clang-format on

    Square() : sq(underlying::NO_SQ) {}

    Square(int sq) : sq(static_cast<underlying>(sq)) { assert(sq <= 64 && sq >= 0); }
    Square(File file, Rank rank) : sq(static_cast<underlying>(file + rank * 8)) {}
    Square(Rank rank, File file) : sq(static_cast<underlying>(file + rank * 8)) {}
    Square(underlying sq) : sq(sq) {}
    Square(bpstd::string_view str) : sq(static_cast<underlying>((str[0] - 'a') + (str[1] - '1') * 8)) {
        assert(str.size() >= 2);
    }

    Square operator^(const Square& s) const noexcept {
        return Square(static_cast<underlying>(static_cast<int>(sq) ^ s.index()));
    };

    bool operator==(const Square& rhs) const noexcept { return sq == rhs.sq; }

    bool operator!=(const Square& rhs) const noexcept { return sq != rhs.sq; }

    bool operator>(const Square& rhs) const noexcept {
        return static_cast<int>(sq) > static_cast<int>(rhs.sq);
    }

    bool operator>=(const Square& rhs) const noexcept {
        return static_cast<int>(sq) >= static_cast<int>(rhs.sq);
    }

    bool operator<(const Square& rhs) const noexcept {
        return static_cast<int>(sq) < static_cast<int>(rhs.sq);
    }

    bool operator<=(const Square& rhs) const noexcept {
        return static_cast<int>(sq) <= static_cast<int>(rhs.sq);
    }

    Square operator+(const Square& rhs) const noexcept {
        return Square(static_cast<underlying>(static_cast<int>(sq) + static_cast<int>(rhs.sq)));
    }

    Square operator-(const Square& rhs) const noexcept {
        return Square(static_cast<underlying>(static_cast<int>(sq) - static_cast<int>(rhs.sq)));
    }

    Square& operator++() noexcept {
        sq = static_cast<underlying>(static_cast<int>(sq) + 1);
        return *this;
    }

    Square operator++(int) noexcept {
        Square tmp(*this);
        operator++();
        return tmp;
    }

    Square& operator--() noexcept {
        sq = static_cast<underlying>(static_cast<int>(sq) - 1);
        return *this;
    }

    Square operator--(int) noexcept {
        Square tmp(*this);
        operator--();
        return tmp;
    }

    operator std::string() const {
        std::string str;
        str += static_cast<std::string>(file());
        str += static_cast<std::string>(rank());
        return str;
    }

    int index() const noexcept { return static_cast<int>(sq); }

    File file() const noexcept { return File(index() & 7); }
    Rank rank() const noexcept { return Rank(index() >> 3); }

    bool is_light() const noexcept {
        return (static_cast<std::int8_t>(sq) / 8 + static_cast<std::int8_t>(sq) % 8) % 2 == 0;
    }
    bool is_dark() const noexcept { return !is_light(); }

    bool is_valid() const noexcept { return static_cast<std::int8_t>(sq) < 64; }

    static bool is_valid(Rank r, File f) noexcept {
        return r >= Rank::RANK_1 && r <= Rank::RANK_8 && f >= File::FILE_A && f <= File::FILE_H;
    }

    static int distance(Square sq, Square sq2) noexcept {
        return std::max(std::abs(sq.file() - sq2.file()), std::abs(sq.rank() - sq2.rank()));
    }

    static int value_distance(Square sq, Square sq2) noexcept {
        return std::abs(sq.index() - sq2.index());
    }

    static bool same_color(Square sq, Square sq2) noexcept {
        return ((9 * (sq ^ sq2).index()) & 8) == 0;
    }

    static bool back_rank(Square sq, Color color) noexcept {
        if (color == Color::WHITE)
            return sq.rank() == Rank::RANK_1;
        else
            return sq.rank() == Rank::RANK_8;
    }

    /// @brief Flips the square vertically.
    Square& flip() noexcept {
        sq = static_cast<underlying>(static_cast<int>(sq) ^ 56);
        return *this;
    }

    /// @brief Conditionally flips the square vertically.
    /// @param c
    /// @return
    Square relative_square(Color c) const noexcept {
        return Square(static_cast<int>(sq) ^ (c * 56));
    }

    int diagonal_of() const noexcept { return 7 + rank() - file(); }

    int antidiagonal_of() const noexcept { return rank() + file(); }

    Square ep_square() const noexcept {
        assert(rank() == Rank::RANK_3     // capture
               || rank() == Rank::RANK_4  // push
               || rank() == Rank::RANK_5  // push
               || rank() == Rank::RANK_6  // capture
        );
        return Square(static_cast<int>(sq) ^ 8);
    }

    static Square castling_king_square(bool is_king_side, Color c) noexcept {
        return Square(is_king_side ? Square::underlying::SQ_G1 : Square::underlying::SQ_C1).relative_square(c);
    }

    static Square castling_rook_square(bool is_king_side, Color c) noexcept {
        return Square(is_king_side ? Square::underlying::SQ_F1 : Square::underlying::SQ_D1).relative_square(c);
    }

    static int max() noexcept { return 64; }

   private:
    underlying sq;
};

inline std::ostream& operator<<(std::ostream& os, const Square& sq) {
    os << static_cast<std::string>(sq);
    return os;
}

enum class Direction : int8_t {
    NORTH      = 8,
    WEST       = -1,
    SOUTH      = -8,
    EAST       = 1,
    NORTH_EAST = 9,
    NORTH_WEST = 7,
    SOUTH_WEST = -9,
    SOUTH_EAST = -7
};

Square operator+(Square sq, Direction dir) {
    return static_cast<Square>(sq.index() + static_cast<int8_t>(dir));
}

}  // namespace chess
