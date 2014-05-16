#ifndef ELFPARSER_H
#define ELFPARSER_H

#include <fstream>
#include <elf.h>

#include "ElfHeader.h"
#include "ElfSectionHeader.h"


class ElfParser
{
private:
    std::string fileName;
    std::ifstream elfIn;

public:
	ElfParser(const std::string& fileName);

    ElfHeader elfHeader;
    ElfSectionHeader elfSectionHeader;
};

#endif // ELFPARSER_H
