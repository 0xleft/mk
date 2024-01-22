#include <cheats.h>
#include "display.h"
#include "eadkpp.h"
#include "palette.h"
#include <ui/chessui.h>
// #include <chess/src/include.hpp>
#include <chess/src/bitboard.hpp>

using U64 = std::uint64_t;
struct Magic {
    U64 mask;
    U64 magic;
    chess::Bitboard attacks[4096];
    U64 shift;
};

namespace chess {
    namespace attacks {
        Magic BishopTable[64] = {};
        Magic RookTable[64] = {};
    }
}

#include "../pregenerator/hdmagics/hdmagics.hpp"


extern const char eadk_app_name[] __attribute__((section(".rodata.eadk_app_name"))) = "MK";
extern const uint32_t eadk_api_level __attribute__((section(".rodata.eadk_api_level"))) = 0;

int main(int argc, char* argv[]) {
    chess::attacks::BishopTable[0];

	return 0;
}