#ifndef ELFSECTIONHEADER_H
#define ELFSECTIONHEADER_H

#include <vector>
#include <list>
#include <memory>
#include <elf.h>

#include "ElfSectionStringTable.h"

class ElfParser;
class SymbolTable;
class ElfSectionHeader
{
public:
    ElfSectionHeader(ElfParser& wElfParser);
    ~ElfSectionHeader();

    void readSymbolTable(SymbolTable& symbolTable);

    ElfParser& elfParser;

private:
    const Elf64_Shdr* getStringTableHeader() const;

    std::vector<Elf64_Shdr> headers;
    std::unique_ptr<ElfSectionStringTable> elfSectionStringTable;

    int idSymTab;
    int idStrTab;
};

#endif // ELFSECTIONHEADER_H
