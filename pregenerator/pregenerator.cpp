#define CHESS_DEBUG
#define PREGENERATOR

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include <cheats.h>
#include <chess/src/include.hpp>
#include <fstream>

// a hacky solution to instead of using pointers just have it ready

void create_files() {
    for (int i = 0; i < 64; i++) {
        std::ofstream file;
        file.open("hdmagics/hdmagicsbishop" + std::to_string(i) + ".hpp", std::ios_base::app);
        file << "namespace chess {" << std::endl;
        file << "namespace attacks {" << std::endl;
        file << "static int init" << "bishops" << i << " = [](){" << std::endl;
        
        file << "BishopTable[" << i << "] = ";

        chess::attacks::Magic c = chess::attacks::BishopTable[i];
        std::string bitboards = "";
        for (int j = 0; j < 512; j++) {
            bitboards += "chess::Bitboard(" + std::to_string(c.attacks[j].getBits()) + "ULL)";
            if (j != 511) {
                bitboards += ",";
            }
        }

        std::string to_append = "Magic{" + std::to_string(c.mask) + "ULL," + std::to_string(c.magic) + "UL,{" + bitboards + "}," + std::to_string(c.shift) + "UL};";
        file << to_append << std::endl;
        file << "return 0;" << std::endl;
        file << "}();" << std::endl;
        file << "}" << std::endl;
        file << "}" << std::endl;
        file.close();
    }

    for (int i = 0; i < 64; i++) {
        std::ofstream file;
        file.open("hdmagics/hdmagicsrook" + std::to_string(i) + ".hpp", std::ios_base::app);
        file << "namespace chess {" << std::endl;
        file << "namespace attacks {" << std::endl;
        file << "static int init" << "rooks" << i << " = [](){" << std::endl;
        
        file << "RookTable[" << i << "] = ";

        chess::attacks::Magic c = chess::attacks::RookTable[i];
        std::string bitboards = "";
        for (int j = 0; j < 4096; j++) {
            bitboards += "chess::Bitboard(" + std::to_string(c.attacks[j].getBits()) + "ULL)";
            if (j != 4095) {
                bitboards += ",";
            }
        }

        std::string to_append = "Magic{" + std::to_string(c.mask) + "ULL," + std::to_string(c.magic) + "UL,{" + bitboards + "}," + std::to_string(c.shift) + "UL};";
        file << to_append << std::endl;
        file << "return 0;" << std::endl;
        file << "}();" << std::endl;
        file << "}" << std::endl;
        file << "}" << std::endl;
        file.close();
    }

    // create the include file
    std::ofstream file;
    file.open("hdmagics/hdmagics.hpp", std::ios_base::app);
    file << "#pragma once" << std::endl;
    for (int i = 0; i < 64; i++) {
        file << "#include \"hdmagicsbishop" << i << ".hpp\"" << std::endl;
    }
    for (int i = 0; i < 64; i++) {
        file << "#include \"hdmagicsrook" << i << ".hpp\"" << std::endl;
    }

    file.close();
}

int main() {
    create_files();
    return 0;
}