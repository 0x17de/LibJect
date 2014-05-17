#ifndef ELFPARSER_H
#define ELFPARSER_H

#include <fstream>
#include <memory>
#include <elf.h>

enum class ElfArch
{
    Unknown,
    Bits32,
    Bits64
};

class ElfHeader;
class ElfSectionHeader;
class ElfProgramHeader;
class SymbolTable;

class ElfParser
{
private:
    void checkArch();

public:
	ElfParser(const std::string& fileName);
	~ElfParser();

	ElfArch arch;
    std::string fileName;
    std::ifstream elfIn;

    std::shared_ptr<SymbolTable> symbolTable;
    std::shared_ptr<ElfHeader> elfHeader;
    std::shared_ptr<ElfSectionHeader> elfSectionHeader;
    std::shared_ptr<ElfProgramHeader> elfProgramHeader;
};

#endif // ELFPARSER_H
