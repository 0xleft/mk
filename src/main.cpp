#include <cheats.h>
#include "display.h"
#include "eadkpp.h"
#include "palette.h"
#include <ui/chessui.h>
#include <chess/src/include.hpp>
#include <chess/src/bitboard.hpp>

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "MK";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

int main(int argc, char* argv[]) {
    chess::Board board = chess::Board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    chess::Movelist moves;
    chess::movegen::legalmoves(moves, board);

	return 0;
}