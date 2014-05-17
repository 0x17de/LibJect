#include <fstream>
#include "ElfProgramHeader.h"
#include "ElfParser.h"
#include "ElfHeader.h"

using namespace std;

ElfProgramHeader::ElfProgramHeader(ElfParser& elfParser)
:
    elfParser(elfParser)
{
    ElfHeader& elfHeader = *elfParser.elfHeader.get();
    ifstream& elfIn = elfParser.elfIn;
}

ElfProgramHeader::~ElfProgramHeader()
{
}
