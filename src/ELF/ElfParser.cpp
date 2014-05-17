#include <stdexcept>

#include "ElfParser.h"
#include "ElfHeader.h"
#include "ElfSectionHeader.h"
#include "ElfProgramHeader.h"
#include "SymbolTable.h"

using namespace std;

ElfParser::ElfParser(const std::string& fileName)
:
    fileName(fileName),
    elfIn(fileName)
{
    checkArch();

    symbolTable.reset(new SymbolTable());
    elfHeader.reset(new ElfHeader(elfIn));
    elfSectionHeader.reset(new ElfSectionHeader(*this));
    elfSectionHeader->readSymbolTable(*symbolTable.get());
    elfProgramHeader.reset(new ElfProgramHeader(*this));
}

ElfParser::~ElfParser()
{
}

void ElfParser::checkArch()
{
    char magicnum[5];
    elfIn.seekg(0);
    elfIn.read(magicnum, 5);
    if (magicnum[0] == ELFMAG0
     && magicnum[1] == ELFMAG1
     && magicnum[2] == ELFMAG2
     && magicnum[3] == ELFMAG3)
    {
        switch(magicnum[4])
        {
        case ELFCLASS32:
            arch = ElfArch::Bits32; break;
        case ELFCLASS64:
            arch = ElfArch::Bits64; break;
        default:
            arch = ElfArch::Unknown; break;
        }
        if (arch != ElfArch::Bits64)
            throw runtime_error("Other than 64 bits not yet supported / will be implemented with templates");
    }
}
