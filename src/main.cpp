#include <cheats.h>
#include "display.h"
#include "eadkpp.h"
#include "palette.h"
#include <chess/include.h>

extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "MK";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

int main(int argc, char* argv[]) {
	EADK::Display::pushRectUniform(EADK::Screen::Rect, Black);

	Chess::Board board;
    std::vector<Chess::Move> moves = Chess::Generator::getLegalMoves(board);

	while (!Chess::Generator::isEnd(board)) {
		std::vector<Chess::Move> moves = Chess::Generator::getLegalMoves(board);
		Chess::Move m = moves[0];
		board.move(m);
	}

	return 0;
}