#include <cheats.h>
#include "display.h"
#include "eadkpp.h"
#include "palette.h"
#include <ui/chessui.h>
#include <chess/src/include.hpp>

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "MK";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

using namespace chess;

int main(int argc, char* argv[]) {
    EADK::Display::pushRectUniform(EADK::Screen::Rect, Black);
    Board board = Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    Movelist moves;
    movegen::legalmoves(moves, board);

    if (moves.size() == 20) {
        EADK::Display::pushRectUniform(EADK::Screen::Rect, Green);
    } else {
        EADK::Display::pushRectUniform(EADK::Screen::Rect, Red);
    }
    EADK::Timing::msleep(1000);

	return 0;
}