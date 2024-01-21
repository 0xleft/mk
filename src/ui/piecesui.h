#include <chess/include.h>
#include <eadkpp.h>

namespace ChessUI {
    void drawPawn(Chess::Color color, int x, int y) {
        // top
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 5, 10, 5}, color == Chess::Color::WHITE ? White : Black);
        // bottom
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 20, 10, 5}, color == Chess::Color::WHITE ? White : Black);
        // body
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 10, 10, 10}, color == Chess::Color::WHITE ? White : Black);
    }

    void drawKnight(Chess::Color color, int x, int y) {
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 5, 10, 5}, color == Chess::Color::WHITE ? White : Black);
        // bottom
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 20, 10, 5}, color == Chess::Color::WHITE ? White : Black);
        // body
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 10, 10, 10}, color == Chess::Color::WHITE ? White : Black);
    }

    void drawBishop(Chess::Color color, int x, int y) {
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 5, 10, 5}, color == Chess::Color::WHITE ? White : Black);
        // bottom
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 20, 10, 5}, color == Chess::Color::WHITE ? White : Black);
        // body
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 10, 10, 10}, color == Chess::Color::WHITE ? White : Black);
    }

    void drawRook(Chess::Color color, int x, int y) {
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 5, 10, 5}, color == Chess::Color::WHITE ? White : Black);
        // bottom
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 20, 10, 5}, color == Chess::Color::WHITE ? White : Black);
        // body
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 10, 10, 10}, color == Chess::Color::WHITE ? White : Black);
    }

    void drawQueen(Chess::Color color, int x, int y) {
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 5, 10, 5}, color == Chess::Color::WHITE ? White : Black);
        // bottom
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 20, 10, 5}, color == Chess::Color::WHITE ? White : Black);
        // body
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 10, 10, 10}, color == Chess::Color::WHITE ? White : Black);
    }

    void drawKing(Chess::Color color, int x, int y) {
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 5, 10, 5}, color == Chess::Color::WHITE ? White : Black);
        // bottom
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 20, 10, 5}, color == Chess::Color::WHITE ? White : Black);
        // body
        EADK::Display::pushRectUniform({x * 30 + 10, y * 30 + 10, 10, 10}, color == Chess::Color::WHITE ? White : Black);
    }
}