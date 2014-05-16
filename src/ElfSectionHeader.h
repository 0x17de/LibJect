#ifndef ELFSECTIONHEADER_H
#define ELFSECTIONHEADER_H

#include <fstream>
#include <vector>
#include <list>
#include <memory>
#include <elf.h>

#include "ElfHeader.h"
#include "ElfSectionStringTable.h"

class ElfSectionHeader
{
public:
    ElfSectionHeader(std::ifstream& elfIn, ElfHeader& elfHeader);
    const ElfHeader& elfHeader;

private:
    const Elf64_Shdr* getStringTableHeader() const;

    std::vector<Elf64_Shdr> headers;
    std::unique_ptr<ElfSectionStringTable> elfSectionStringTable;
    std::list<ElfSectionStringTable> additionalSymbolTables;

    int idSymTab;
    int idStrTab;
};

#endif // ELFSECTIONHEADER_H
